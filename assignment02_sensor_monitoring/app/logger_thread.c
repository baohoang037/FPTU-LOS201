/**
 * @file logger_thread.c
 * @brief Implementation of Logger Thread
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include "logger_thread.h"

static void check_and_rotate_log(FILE **fp)
{
    long size = ftell(*fp);
    if (size >= LOG_MAX_FILE_SIZE) {
        fclose(*fp);
        rename(LOG_FILE_PATH, LOG_BACKUP_PATH);
        *fp = fopen(LOG_FILE_PATH, "a");
        if (!*fp) {
            perror("Failed to recreate log file after rotation");
        }
    }
}

int logger_init(logger_context_t *ctx)
{
    if (!ctx) return -1;
    ctx->running = false;
    ctx->total_logs_written = 0;

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; /* Standard Linux unprivileged limit */
    attr.mq_msgsize = sizeof(log_msg_t);
    attr.mq_curmsgs = 0;

    mq_unlink(LOG_QUEUE_NAME);
    ctx->log_mq = mq_open(LOG_QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (ctx->log_mq == (mqd_t)-1) {
        perror("mq_open logger");
        return -1;
    }
    return 0;
}

bool logger_send(logger_context_t *ctx, const char *msg)
{
    if (!ctx || !msg || ctx->log_mq == (mqd_t)-1) return false;
    log_msg_t item;
    strncpy(item.message, msg, LOG_MSG_MAX_LEN - 1);
    item.message[LOG_MSG_MAX_LEN - 1] = '\0';

    if (mq_send(ctx->log_mq, (const char *)&item, sizeof(item), 0) != 0) {
        return false;
    }
    return true;
}

void logger_stop(logger_context_t *ctx)
{
    if (!ctx) return;
    ctx->running = false;
    logger_send(ctx, "SHUTDOWN");
    if (ctx->thread_id) {
        pthread_join(ctx->thread_id, NULL);
    }
    if (ctx->log_mq != (mqd_t)-1) {
        mq_close(ctx->log_mq);
        mq_unlink(LOG_QUEUE_NAME);
    }
}

void *logger_thread_func(void *arg)
{
    logger_context_t *ctx = (logger_context_t *)arg;
    ctx->running = true;

    FILE *fp = fopen(LOG_FILE_PATH, "a");
    if (!fp) {
        perror("fopen /tmp/sms.log");
        return NULL;
    }

    log_msg_t item;
    time_t last_flush_time = time(NULL);

    while (ctx->running) {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += 1; /* Wait up to 1s to allow periodic flush */

        ssize_t bytes_read = mq_timedreceive(ctx->log_mq, (char *)&item, sizeof(item), NULL, &ts);
        if (bytes_read > 0) {
            if (strcmp(item.message, "SHUTDOWN") == 0) {
                break;
            }
            fprintf(fp, "%s\n", item.message);
            ctx->total_logs_written++;
            check_and_rotate_log(&fp);
        }

        /* Flush periodically every 5 seconds */
        time_t now = time(NULL);
        if (now - last_flush_time >= 5) {
            fflush(fp);
            last_flush_time = now;
        }
    }

    /* Final flush before shutdown */
    fflush(fp);
    fclose(fp);
    return NULL;
}
