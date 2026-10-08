/**
 * @file alert_thread.h
 * @brief Alert Thread handling alarms via POSIX message queue
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#ifndef ALERT_THREAD_H
#define ALERT_THREAD_H

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <mqueue.h>
#include "logger_thread.h"

#define ALARM_QUEUE_NAME "/sms_alarm_queue"

typedef enum {
    ALERT_TYPE_TEMP_HIGH = 0,
    ALERT_TYPE_HUMID_HIGH,
    ALERT_TYPE_TEMP_SPIKE
} alert_type_t;

typedef struct {
    alert_type_t type;
    uint64_t timestamp_ms;
    float value;
    float threshold;
} alarm_msg_t;

typedef struct {
    mqd_t alarm_mq;
    bool running;
    pthread_t thread_id;
    logger_context_t *logger_ctx;

    /* Metrics */
    uint32_t count_temp_high;
    uint32_t count_humid_high;
    uint32_t count_temp_spike;
} alert_context_t;

int alert_init(alert_context_t *ctx, logger_context_t *logger_ctx);
void alert_stop(alert_context_t *ctx);
bool alert_send(alert_context_t *ctx, const alarm_msg_t *alarm);
void *alert_thread_func(void *arg);

#endif /* ALERT_THREAD_H */
