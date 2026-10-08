/**
 * @file circular_buffer.c
 * @brief Implementation of Thread-safe Circular Buffer
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circular_buffer.h"

int circular_buffer_init(circular_buffer_t *cb, size_t capacity)
{
    if (!cb || capacity == 0)
        return -1;

    cb->capacity = capacity;
    cb->data = (sms_sensor_data_t *)malloc(sizeof(sms_sensor_data_t) * capacity);
    if (!cb->data) {
        perror("malloc circular buffer");
        return -1;
    }

    cb->head = 0;
    cb->tail = 0;
    cb->current_size = 0;
    cb->total_produced = 0;
    cb->total_consumed = 0;
    cb->overflow_count = 0;
    cb->is_shutdown = false;

    if (pthread_mutex_init(&cb->lock, NULL) != 0) {
        free(cb->data);
        return -1;
    }

    if (pthread_cond_init(&cb->not_empty, NULL) != 0) {
        pthread_mutex_destroy(&cb->lock);
        free(cb->data);
        return -1;
    }

    return 0;
}

void circular_buffer_destroy(circular_buffer_t *cb)
{
    if (!cb)
        return;

    pthread_mutex_lock(&cb->lock);
    cb->is_shutdown = true;
    if (cb->data) {
        free(cb->data);
        cb->data = NULL;
    }
    pthread_mutex_unlock(&cb->lock);

    pthread_mutex_destroy(&cb->lock);
    pthread_cond_destroy(&cb->not_empty);
}

void circular_buffer_shutdown(circular_buffer_t *cb)
{
    if (!cb)
        return;

    pthread_mutex_lock(&cb->lock);
    cb->is_shutdown = true;
    /* Wake up any waiting consumers */
    pthread_cond_broadcast(&cb->not_empty);
    pthread_mutex_unlock(&cb->lock);
}

bool circular_buffer_push(circular_buffer_t *cb, const sms_sensor_data_t *item)
{
    if (!cb || !item)
        return false;

    pthread_mutex_lock(&cb->lock);

    if (cb->is_shutdown) {
        pthread_mutex_unlock(&cb->lock);
        return false;
    }

    /* If buffer is full, drop sample and increment overflow counter */
    if (cb->current_size >= cb->capacity) {
        cb->overflow_count++;
        pthread_mutex_unlock(&cb->lock);
        return false;
    }

    cb->data[cb->head] = *item;
    cb->head = (cb->head + 1) % cb->capacity;
    cb->current_size++;
    cb->total_produced++;

    /* Signal consumer that new data is available */
    pthread_cond_signal(&cb->not_empty);

    pthread_mutex_unlock(&cb->lock);
    return true;
}

bool circular_buffer_pop(circular_buffer_t *cb, sms_sensor_data_t *item)
{
    if (!cb || !item)
        return false;

    pthread_mutex_lock(&cb->lock);

    /* Wait while empty, unless shutdown has been triggered */
    while (cb->current_size == 0 && !cb->is_shutdown) {
        pthread_cond_wait(&cb->not_empty, &cb->lock);
    }

    if (cb->current_size == 0 && cb->is_shutdown) {
        pthread_mutex_unlock(&cb->lock);
        return false;
    }

    *item = cb->data[cb->tail];
    cb->tail = (cb->tail + 1) % cb->capacity;
    cb->current_size--;
    cb->total_consumed++;

    pthread_mutex_unlock(&cb->lock);
    return true;
}

void circular_buffer_get_stats(circular_buffer_t *cb, circular_buffer_stats_t *stats)
{
    if (!cb || !stats)
        return;

    pthread_mutex_lock(&cb->lock);
    stats->capacity = cb->capacity;
    stats->current_size = cb->current_size;
    stats->total_produced = cb->total_produced;
    stats->total_consumed = cb->total_consumed;
    stats->overflow_count = cb->overflow_count;
    pthread_mutex_unlock(&cb->lock);
}
