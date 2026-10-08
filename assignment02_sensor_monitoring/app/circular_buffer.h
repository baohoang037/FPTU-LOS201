/**
 * @file circular_buffer.h
 * @brief Thread-safe Circular Buffer implementation for Sensor Data
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "sms_sensor.h"

#define CIRCULAR_BUFFER_DEFAULT_CAPACITY 64

typedef struct {
    sms_sensor_data_t *data;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t current_size;

    /* Metrics & Statistics */
    uint64_t total_produced;
    uint64_t total_consumed;
    uint64_t overflow_count;

    /* Synchronization primitives */
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    bool is_shutdown;
} circular_buffer_t;

typedef struct {
    size_t current_size;
    size_t capacity;
    uint64_t total_produced;
    uint64_t total_consumed;
    uint64_t overflow_count;
} circular_buffer_stats_t;

/* APIs */
int circular_buffer_init(circular_buffer_t *cb, size_t capacity);
void circular_buffer_destroy(circular_buffer_t *cb);
void circular_buffer_shutdown(circular_buffer_t *cb);

/* Producer operation (Non-blocking, drop sample if full) */
bool circular_buffer_push(circular_buffer_t *cb, const sms_sensor_data_t *item);

/* Consumer operation (Blocking wait until item available or shutdown) */
bool circular_buffer_pop(circular_buffer_t *cb, sms_sensor_data_t *item);

/* Statistics getter */
void circular_buffer_get_stats(circular_buffer_t *cb, circular_buffer_stats_t *stats);

#endif /* CIRCULAR_BUFFER_H */
