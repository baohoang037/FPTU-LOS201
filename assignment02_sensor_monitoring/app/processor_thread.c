/**
 * @file processor_thread.c
 * @brief Implementation of Processor Thread
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "processor_thread.h"

int processor_init(processor_context_t *ctx,
                   circular_buffer_t *buffer,
                   alert_context_t *alert_ctx,
                   logger_context_t *logger_ctx,
                   float temp_threshold,
                   float humid_threshold)
{
    if (!ctx || !buffer) return -1;
    ctx->buffer = buffer;
    ctx->alert_ctx = alert_ctx;
    ctx->logger_ctx = logger_ctx;
    ctx->temp_threshold = temp_threshold;
    ctx->humid_threshold = humid_threshold;
    ctx->running = false;
    ctx->total_processed = 0;
    return 0;
}

void processor_stop(processor_context_t *ctx)
{
    if (!ctx) return;
    ctx->running = false;
    if (ctx->thread_id) {
        pthread_join(ctx->thread_id, NULL);
    }
}

void *processor_thread_func(void *arg)
{
    processor_context_t *ctx = (processor_context_t *)arg;
    ctx->running = true;

    sms_sensor_data_t sample;
    float temp_window[ROLLING_WINDOW_SIZE] = {0};
    float humid_window[ROLLING_WINDOW_SIZE] = {0};
    int window_count = 0;
    int window_idx = 0;

    float prev_temp = -999.0f;
    char log_buf[LOG_MSG_MAX_LEN];

    while (ctx->running) {
        if (!circular_buffer_pop(ctx->buffer, &sample)) {
            /* Buffer stopped or empty on shutdown */
            break;
        }

        ctx->total_processed++;

        /* Update rolling average window */
        temp_window[window_idx] = sample.temperature;
        humid_window[window_idx] = sample.humidity;
        window_idx = (window_idx + 1) % ROLLING_WINDOW_SIZE;
        if (window_count < ROLLING_WINDOW_SIZE) {
            window_count++;
        }

        float sum_t = 0.0f, sum_h = 0.0f;
        for (int i = 0; i < window_count; i++) {
            sum_t += temp_window[i];
            sum_h += humid_window[i];
        }
        float avg_t = sum_t / window_count;
        float avg_h = sum_h / window_count;

        /* Send sample to logger queue */
        if (ctx->logger_ctx) {
            snprintf(log_buf, sizeof(log_buf),
                     "[DATA][%llu] T=%.2fC H=%.2f%% | AvgT=%.2fC AvgH=%.2f%%",
                     (unsigned long long)sample.timestamp_ms,
                     sample.temperature, sample.humidity,
                     avg_t, avg_h);
            logger_send(ctx->logger_ctx, log_buf);
        }

        /* Threshold Check 1: High Temperature */
        if (sample.temperature > ctx->temp_threshold) {
            alarm_msg_t alarm = {
                .type = ALERT_TYPE_TEMP_HIGH,
                .timestamp_ms = sample.timestamp_ms,
                .value = sample.temperature,
                .threshold = ctx->temp_threshold
            };
            alert_send(ctx->alert_ctx, &alarm);
        }

        /* Threshold Check 2: High Humidity */
        if (sample.humidity > ctx->humid_threshold) {
            alarm_msg_t alarm = {
                .type = ALERT_TYPE_HUMID_HIGH,
                .timestamp_ms = sample.timestamp_ms,
                .value = sample.humidity,
                .threshold = ctx->humid_threshold
            };
            alert_send(ctx->alert_ctx, &alarm);
        }

        /* Threshold Check 3: Temperature Spike (> 5.0 °C change) */
        if (prev_temp > -900.0f && fabsf(sample.temperature - prev_temp) > 5.0f) {
            alarm_msg_t alarm = {
                .type = ALERT_TYPE_TEMP_SPIKE,
                .timestamp_ms = sample.timestamp_ms,
                .value = fabsf(sample.temperature - prev_temp),
                .threshold = 5.0f
            };
            alert_send(ctx->alert_ctx, &alarm);
        }

        prev_temp = sample.temperature;
    }
    return NULL;
}
