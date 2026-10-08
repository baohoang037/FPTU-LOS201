/**
 * @file sms_sensor.h
 * @brief Common header for Sensor Monitoring System (Kernel & Userspace)
 * @author Hoang Ngoc Gia Bao
 * @date 2026-10-08
 */

#ifndef SMS_SENSOR_H
#define SMS_SENSOR_H

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/ioctl.h>
#else
#include <stdint.h>
#include <sys/ioctl.h>
#endif

#define DEVICE_NAME         "sms_sensor"
#define DEVICE_PATH         "/dev/sms_sensor"
#define PROC_FILENAME       "sms_stats"
#define DEFAULT_SAMPLE_MS   500
#define MIN_INTERVAL_MS     100

/* ioctl definition */
#define SMS_IOCTL_MAGIC     's'
#define SMS_SET_INTERVAL    _IOW(SMS_IOCTL_MAGIC, 1, uint32_t)

/* Struct for internal sensor data */
typedef struct {
    uint64_t timestamp_ms;
    float temperature;   /* °C */
    float humidity;      /* % */
} sms_sensor_data_t;

#endif /* SMS_SENSOR_H */
