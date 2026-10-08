/**
 * @file sensor_thread.c
 * @brief Implementation of Sensor Reading Thread
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include "sensor_thread.h"
#include "sms_sensor.h"

static long timespec_diff_us(const struct timespec *a, const struct timespec *b)
{
    return (long)((a->tv_sec - b->tv_sec) * 1000000L + (a->tv_nsec - b->tv_nsec) / 1000L);
}

int sensor_init(sensor_context_t *ctx,
                const char *dev_path,
                uint32_t interval_ms,
                bool verbose,
                bool use_rt,
                circular_buffer_t *buffer)
{
    if (!ctx || !buffer) return -1;
    strncpy(ctx->dev_path, dev_path ? dev_path : DEVICE_PATH, sizeof(ctx->dev_path) - 1);
    ctx->interval_ms = interval_ms ? interval_ms : DEFAULT_SAMPLE_MS;
    ctx->verbose = verbose;
    ctx->use_rt = use_rt;
    ctx->buffer = buffer;
    ctx->running = false;
    ctx->total_samples_read = 0;
    ctx->jitter_count = 0;
    return 0;
}

void sensor_stop(sensor_context_t *ctx)
{
    if (!ctx) return;
    ctx->running = false;
    if (ctx->thread_id) {
        pthread_join(ctx->thread_id, NULL);
    }
}

void *sensor_thread_func(void *arg)
{
    sensor_context_t *ctx = (sensor_context_t *)arg;
    ctx->running = true;

    if (ctx->use_rt) {
        struct sched_param sp;
        sp.sched_priority = 50;
        if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp) == 0) {
            printf("[RT] Sensor Thread configured with SCHED_FIFO, priority 50\n");
        } else {
            perror("[RT Warning] Failed to set SCHED_FIFO (run with sudo for RT priority)");
        }
    }

    int fd = open(ctx->dev_path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error opening sensor device %s: %s\n", ctx->dev_path, strerror(errno));
        return NULL;
    }

    uint32_t driver_interval = ctx->interval_ms;
    ioctl(fd, SMS_SET_INTERVAL, &driver_interval);

    struct timespec next_wakeup, actual_wakeup;
    clock_gettime(CLOCK_MONOTONIC, &next_wakeup);

    char buf[128];

    while (ctx->running) {
        next_wakeup.tv_sec += ctx->interval_ms / 1000;
        next_wakeup.tv_nsec += (ctx->interval_ms % 1000) * 1000000L;
        if (next_wakeup.tv_nsec >= 1000000000L) {
            next_wakeup.tv_sec += 1;
            next_wakeup.tv_nsec -= 1000000000L;
        }

        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_wakeup, NULL);

        clock_gettime(CLOCK_MONOTONIC, &actual_wakeup);
        long jitter = labs(timespec_diff_us(&actual_wakeup, &next_wakeup));
        if (ctx->jitter_count < MAX_JITTER_SAMPLES) {
            ctx->jitter_us[ctx->jitter_count++] = jitter;
        }

        lseek(fd, 0, SEEK_SET);
        ssize_t bytes = read(fd, buf, sizeof(buf) - 1);
        if (bytes < 0 && (errno == EAGAIN || errno == EINTR)) {
            usleep(10000); /* Retry after 10ms */
            lseek(fd, 0, SEEK_SET);
            bytes = read(fd, buf, sizeof(buf) - 1);
        }

        if (bytes > 0) {
            buf[bytes] = '\0';
            sms_sensor_data_t sample;
            unsigned long long ts;
            if (sscanf(buf, "%llu,%f,%f", &ts, &sample.temperature, &sample.humidity) == 3) {
                sample.timestamp_ms = (uint64_t)ts;
                ctx->total_samples_read++;

                if (ctx->verbose) {
                    printf("[SENSOR] Sample #%lu: Time=%llu, Temp=%.2f C, Humid=%.2f %%\n",
                           ctx->total_samples_read, (unsigned long long)sample.timestamp_ms,
                           sample.temperature, sample.humidity);
                }

                if (!circular_buffer_push(ctx->buffer, &sample)) {
                    fprintf(stderr, "[WARN] Circular buffer full! Dropping sample #%lu\n",
                            ctx->total_samples_read);
                }
            }
        }
    }

    close(fd);
    return NULL;
}

static int compare_long(const void *a, const void *b)
{
    long la = *(const long *)a;
    long lb = *(const long *)b;
    return (la > lb) - (la < lb);
}

void sensor_print_jitter_report(const sensor_context_t *ctx, const char *outfile)
{
    if (!ctx || ctx->jitter_count == 0) return;

    FILE *out = stdout;
    FILE *fout = NULL;
    if (outfile) {
        fout = fopen(outfile, "w");
        if (fout) out = fout;
    }

    long min_j = ctx->jitter_us[0], max_j = ctx->jitter_us[0];
    double sum = 0;
    long sorted[MAX_JITTER_SAMPLES];

    for (size_t i = 0; i < ctx->jitter_count; i++) {
        long j = ctx->jitter_us[i];
        if (j < min_j) min_j = j;
        if (j > max_j) max_j = j;
        sum += j;
        sorted[i] = j;
    }
    double avg = sum / ctx->jitter_count;

    qsort(sorted, ctx->jitter_count, sizeof(long), compare_long);
    long p99 = sorted[(size_t)(ctx->jitter_count * 0.99)];

    int b_0_100 = 0, b_100_500 = 0, b_500_1000 = 0, b_over_1000 = 0;
    for (size_t i = 0; i < ctx->jitter_count; i++) {
        long val = sorted[i];
        if (val < 100) b_0_100++;
        else if (val < 500) b_100_500++;
        else if (val < 1000) b_500_1000++;
        else b_over_1000++;
    }

    fprintf(out, "\n================ JITTER REPORT (%s) ================\n",
            ctx->use_rt ? "SCHED_FIFO" : "SCHED_OTHER");
    fprintf(out, "Total samples measured : %zu\n", ctx->jitter_count);
    fprintf(out, "Min jitter             : %ld us\n", min_j);
    fprintf(out, "Avg jitter             : %.2f us\n", avg);
    fprintf(out, "Max jitter             : %ld us\n", max_j);
    fprintf(out, "P99 jitter             : %ld us\n", p99);
    fprintf(out, "----------------- JITTER HISTOGRAM -----------------\n");
    fprintf(out, "  0 -  100 us : %5d (%5.1f%%)\n", b_0_100, (double)b_0_100 * 100.0 / ctx->jitter_count);
    fprintf(out, "100 -  500 us : %5d (%5.1f%%)\n", b_100_500, (double)b_100_500 * 100.0 / ctx->jitter_count);
    fprintf(out, "500 - 1000 us : %5d (%5.1f%%)\n", b_500_1000, (double)b_500_1000 * 100.0 / ctx->jitter_count);
    fprintf(out, "    > 1000 us : %5d (%5.1f%%)\n", b_over_1000, (double)b_over_1000 * 100.0 / ctx->jitter_count);
    fprintf(out, "====================================================\n\n");

    if (fout) fclose(fout);
}
