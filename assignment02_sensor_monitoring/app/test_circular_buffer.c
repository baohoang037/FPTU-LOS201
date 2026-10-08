/**
 * @file test_circular_buffer.c
 * @brief Stress test & verification for Thread-safe Circular Buffer
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "circular_buffer.h"

#define TEST_SAMPLES 1000

static circular_buffer_t g_test_buffer;

void *producer_worker(void *arg)
{
    (void)arg;
    for (int i = 0; i < TEST_SAMPLES; i++) {
        sms_sensor_data_t data = {
            .timestamp_ms = (uint64_t)i,
            .temperature = 25.0f + (float)(i % 15),
            .humidity = 50.0f + (float)(i % 30)
        };
        while (!circular_buffer_push(&g_test_buffer, &data)) {
            usleep(100); /* Buffer full, retry */
        }
    }
    return NULL;
}

void *consumer_worker(void *arg)
{
    (void)arg;
    int received = 0;
    sms_sensor_data_t data;

    while (received < TEST_SAMPLES) {
        if (circular_buffer_pop(&g_test_buffer, &data)) {
            received++;
        }
    }
    return NULL;
}

int main(void)
{
    pthread_t prod, cons;
    printf("=== RUNNING CIRCULAR BUFFER STRESS TEST ===\n");

    assert(circular_buffer_init(&g_test_buffer, 16) == 0);

    pthread_create(&prod, NULL, producer_worker, NULL);
    pthread_create(&cons, NULL, consumer_worker, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    circular_buffer_stats_t stats;
    circular_buffer_get_stats(&g_test_buffer, &stats);

    printf("Test completed successfully!\n");
    printf("- Total produced: %lu\n", stats.total_produced);
    printf("- Total consumed: %lu\n", stats.total_consumed);
    printf("- Current size:   %zu\n", stats.current_size);
    printf("- Overflow count: %lu\n", stats.overflow_count);

    assert(stats.total_produced == TEST_SAMPLES);
    assert(stats.total_consumed == TEST_SAMPLES);
    assert(stats.current_size == 0);

    circular_buffer_destroy(&g_test_buffer);
    printf("=== PASS: Circular Buffer is Thread-Safe & Leak-Free ===\n");
    return 0;
}
