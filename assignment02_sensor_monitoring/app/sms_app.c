/**
 * @file sms_app.c
 * @brief Sensor Monitoring System - Main Application
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <sys/mman.h>

#include "circular_buffer.h"
#include "logger_thread.h"
#include "alert_thread.h"
#include "processor_thread.h"
#include "sensor_thread.h"

static volatile sig_atomic_t g_running = 1;

static void sigint_handler(int signum)
{
    (void)signum;
    g_running = 0;
}

static void print_usage(const char *prog)
{
    printf("Usage: %s [OPTIONS]\n", prog);
    printf("  -i <ms>    Sensor sampling interval (default: 500ms)\n");
    printf("  -t <°C>    Temperature alert threshold (default: 40.0)\n");
    printf("  -h <%%>     Humidity alert threshold (default: 80.0)\n");
    printf("  -d <sec>   Run duration in seconds, 0 = infinite (default: 60)\n");
    printf("  -v         Verbose mode: print each sample to stdout\n");
    printf("  -r         Enable Real-Time SCHED_FIFO for Sensor Thread\n");
}

int main(int argc, char *argv[])
{
    uint32_t interval_ms = 500;
    float temp_thresh = 40.0f;
    float humid_thresh = 80.0f;
    int duration_sec = 60;
    bool verbose = false;
    bool use_rt = false;

    int opt;
    while ((opt = getopt(argc, argv, "i:t:h:d:vr")) != -1) {
        switch (opt) {
        case 'i': interval_ms = (uint32_t)atoi(optarg); break;
        case 't': temp_thresh = (float)atof(optarg); break;
        case 'h': humid_thresh = (float)atof(optarg); break;
        case 'd': duration_sec = atoi(optarg); break;
        case 'v': verbose = true; break;
        case 'r': use_rt = true; break;
        default:
            print_usage(argv[0]);
            return 1;
        }
    }

    printf("====================================================\n");
    printf("       SENSOR MONITORING SYSTEM (SMS) STARTED       \n");
    printf("====================================================\n");
    printf("Interval: %u ms | Temp Thresh: %.1f C | Humid Thresh: %.1f %%\n",
           interval_ms, temp_thresh, humid_thresh);
    printf("Duration: %d s  | Verbose: %s | RT Mode: %s\n\n",
           duration_sec, verbose ? "ON" : "OFF", use_rt ? "SCHED_FIFO" : "SCHED_OTHER");

    /* Lock memory pages if RT mode */
    if (use_rt) {
        if (mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
            perror("[RT Warning] mlockall failed");
        }
    }

    /* Signal handler for Graceful Shutdown */
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sigint_handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    /* 1. Init shared circular buffer */
    circular_buffer_t buffer;
    if (circular_buffer_init(&buffer, CIRCULAR_BUFFER_DEFAULT_CAPACITY) != 0) {
        fprintf(stderr, "Failed to init circular buffer\n");
        return 1;
    }

    /* 2. Init Logger Thread */
    logger_context_t logger_ctx;
    if (logger_init(&logger_ctx) != 0) {
        fprintf(stderr, "Failed to init logger\n");
        circular_buffer_destroy(&buffer);
        return 1;
    }
    pthread_create(&logger_ctx.thread_id, NULL, logger_thread_func, &logger_ctx);

    /* 3. Init Alert Thread */
    alert_context_t alert_ctx;
    if (alert_init(&alert_ctx, &logger_ctx) != 0) {
        fprintf(stderr, "Failed to init alert system\n");
        logger_stop(&logger_ctx);
        circular_buffer_destroy(&buffer);
        return 1;
    }
    pthread_create(&alert_ctx.thread_id, NULL, alert_thread_func, &alert_ctx);

    /* 4. Init Processor Thread */
    processor_context_t proc_ctx;
    processor_init(&proc_ctx, &buffer, &alert_ctx, &logger_ctx, temp_thresh, humid_thresh);
    pthread_create(&proc_ctx.thread_id, NULL, processor_thread_func, &proc_ctx);

    /* 5. Init Sensor Thread */
    sensor_context_t sensor_ctx;
    sensor_init(&sensor_ctx, DEVICE_PATH, interval_ms, verbose, use_rt, &buffer);
    pthread_create(&sensor_ctx.thread_id, NULL, sensor_thread_func, &sensor_ctx);

    /* Main loop: wait for duration or SIGINT */
    int elapsed = 0;
    while (g_running && (duration_sec == 0 || elapsed < duration_sec)) {
        sleep(1);
        elapsed++;
    }

    printf("\nInitiating graceful shutdown...\n");

    /* Graceful Shutdown sequence */
    sensor_stop(&sensor_ctx);
    circular_buffer_shutdown(&buffer);
    processor_stop(&proc_ctx);
    alert_stop(&alert_ctx);
    logger_stop(&logger_ctx);

    /* Print Summary Report */
    circular_buffer_stats_t cb_stats;
    circular_buffer_get_stats(&buffer, &cb_stats);

    printf("\n================ SYSTEM SUMMARY ================\n");
    printf("Elapsed Runtime         : %d seconds\n", elapsed);
    printf("Total Samples Read      : %lu\n", sensor_ctx.total_samples_read);
    printf("Total Samples Processed : %lu\n", proc_ctx.total_processed);
    printf("Buffer Overflows        : %lu\n", cb_stats.overflow_count);
    printf("Total Logs Written      : %lu\n", logger_ctx.total_logs_written);
    printf("Alerts Summary:\n");
    printf("  - High Temperature    : %u\n", alert_ctx.count_temp_high);
    printf("  - High Humidity       : %u\n", alert_ctx.count_humid_high);
    printf("  - Temperature Spikes  : %u\n", alert_ctx.count_temp_spike);
    printf("================================================\n");

    /* Export Jitter Report */
    sensor_print_jitter_report(&sensor_ctx, NULL);

    /* Clean up resources */
    circular_buffer_destroy(&buffer);

    printf("Shutdown clean. Exit code 0.\n");
    return 0;
}
