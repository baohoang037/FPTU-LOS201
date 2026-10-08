/**
 * @file processor_thread.h
 * @brief Data processing and threshold detection
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#ifndef PROCESSOR_THREAD_H
#define PROCESSOR_THREAD_H

#include <pthread.h>
#include <stdbool.h>
#include "circular_buffer.h"
#include "alert_thread.h"
#include "logger_thread.h"

#define ROLLING_WINDOW_SIZE 10

typedef struct {
    circular_buffer_t *buffer;
    alert_context_t *alert_ctx;
    logger_context_t *logger_ctx;
    float temp_threshold;
    float humid_threshold;
    bool running;
    pthread_t thread_id;

    /* Metrics */
    uint64_t total_processed;
} processor_context_t;

int processor_init(processor_context_t *ctx,
                   circular_buffer_t *buffer,
                   alert_context_t *alert_ctx,
                   logger_context_t *logger_ctx,
                   float temp_threshold,
                   float humid_threshold);
void processor_stop(processor_context_t *ctx);
void *processor_thread_func(void *arg);

#endif /* PROCESSOR_THREAD_H */
