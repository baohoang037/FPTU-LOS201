/**
 * @file sensor_thread.h
 * @brief Sensor reading thread with RT scheduling & latency measurement
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#ifndef SENSOR_THREAD_H
#define SENSOR_THREAD_H

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include "circular_buffer.h"

#define MAX_JITTER_SAMPLES 2000

typedef struct {
    char dev_path[64];
    uint32_t interval_ms;
    bool verbose;
    bool use_rt;
    circular_buffer_t *buffer;
    bool running;
    pthread_t thread_id;

    /* Metrics & Latency */
    uint64_t total_samples_read;
    long jitter_us[MAX_JITTER_SAMPLES];
    size_t jitter_count;
} sensor_context_t;

int sensor_init(sensor_context_t *ctx,
                const char *dev_path,
                uint32_t interval_ms,
                bool verbose,
                bool use_rt,
                circular_buffer_t *buffer);
void sensor_stop(sensor_context_t *ctx);
void *sensor_thread_func(void *arg);
void sensor_print_jitter_report(const sensor_context_t *ctx, const char *outfile);

#endif /* SENSOR_THREAD_H */
