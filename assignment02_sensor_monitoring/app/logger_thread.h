/**
 * @file logger_thread.h
 * @brief Logger Thread with log rotation and periodic flushing
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#ifndef LOGGER_THREAD_H
#define LOGGER_THREAD_H

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <mqueue.h>

#define LOG_QUEUE_NAME    "/sms_log_queue"
#define LOG_FILE_PATH     "/tmp/sms.log"
#define LOG_BACKUP_PATH   "/tmp/sms.log.1"
#define LOG_MAX_FILE_SIZE (1024 * 1024) /* 1MB */
#define LOG_MSG_MAX_LEN   256

typedef struct {
    char message[LOG_MSG_MAX_LEN];
} log_msg_t;

typedef struct {
    mqd_t log_mq;
    bool running;
    pthread_t thread_id;
    uint64_t total_logs_written;
} logger_context_t;

int logger_init(logger_context_t *ctx);
void logger_stop(logger_context_t *ctx);
bool logger_send(logger_context_t *ctx, const char *msg);
void *logger_thread_func(void *arg);

#endif /* LOGGER_THREAD_H */
