/**
 * @file alert_thread.c
 * @brief Implementation of Alert Thread
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "alert_thread.h"

static const char *get_alert_type_str(alert_type_t type)
{
    switch (type) {
    case ALERT_TYPE_TEMP_HIGH:  return "TEMP_HIGH";
    case ALERT_TYPE_HUMID_HIGH: return "HUMID_HIGH";
    case ALERT_TYPE_TEMP_SPIKE: return "TEMP_SPIKE";
    default:                    return "UNKNOWN";
    }
}

int alert_init(alert_context_t *ctx, logger_context_t *logger_ctx)
{
    if (!ctx) return -1;
    ctx->running = false;
    ctx->logger_ctx = logger_ctx;
    ctx->count_temp_high = 0;
    ctx->count_humid_high = 0;
    ctx->count_temp_spike = 0;

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; /* Standard Linux unprivileged limit */
    attr.mq_msgsize = sizeof(alarm_msg_t);
    attr.mq_curmsgs = 0;

    mq_unlink(ALARM_QUEUE_NAME);
    ctx->alarm_mq = mq_open(ALARM_QUEUE_NAME, O_CREAT | O_RDWR, 0666, &attr);
    if (ctx->alarm_mq == (mqd_t)-1) {
        perror("mq_open alert");
        return -1;
    }
    return 0;
}

bool alert_send(alert_context_t *ctx, const alarm_msg_t *alarm)
{
    if (!ctx || !alarm || ctx->alarm_mq == (mqd_t)-1) return false;
    if (mq_send(ctx->alarm_mq, (const char *)alarm, sizeof(alarm_msg_t), 1) != 0) {
        return false;
    }
    return true;
}

void alert_stop(alert_context_t *ctx)
{
    if (!ctx) return;
    ctx->running = false;

    alarm_msg_t term_msg = { .type = (alert_type_t)-1 };
    alert_send(ctx, &term_msg);

    if (ctx->thread_id) {
        pthread_join(ctx->thread_id, NULL);
    }
    if (ctx->alarm_mq != (mqd_t)-1) {
        mq_close(ctx->alarm_mq);
        mq_unlink(ALARM_QUEUE_NAME);
    }
}

void *alert_thread_func(void *arg)
{
    alert_context_t *ctx = (alert_context_t *)arg;
    ctx->running = true;
    alarm_msg_t alarm;
    char log_buf[LOG_MSG_MAX_LEN];

    while (ctx->running) {
        ssize_t bytes = mq_receive(ctx->alarm_mq, (char *)&alarm, sizeof(alarm), NULL);
        if (bytes <= 0 || (int)alarm.type == -1) {
            break;
        }

        const char *type_str = get_alert_type_str(alarm.type);

        /* Count occurrences */
        if (alarm.type == ALERT_TYPE_TEMP_HIGH) ctx->count_temp_high++;
        else if (alarm.type == ALERT_TYPE_HUMID_HIGH) ctx->count_humid_high++;
        else if (alarm.type == ALERT_TYPE_TEMP_SPIKE) ctx->count_temp_spike++;

        /* Print alert directly to stderr */
        fprintf(stderr, "[ALERT][%llu] TYPE: %s VALUE: %.2f THRESHOLD: %.2f\n",
                (unsigned long long)alarm.timestamp_ms, type_str, alarm.value, alarm.threshold);

        /* Send formatted alert to Logger Thread */
        if (ctx->logger_ctx) {
            snprintf(log_buf, sizeof(log_buf),
                     "[ALERT][%llu] TYPE: %s VALUE: %.2f THRESHOLD: %.2f",
                     (unsigned long long)alarm.timestamp_ms, type_str, alarm.value, alarm.threshold);
            logger_send(ctx->logger_ctx, log_buf);
        }
    }
    return NULL;
}
