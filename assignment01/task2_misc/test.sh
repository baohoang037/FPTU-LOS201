#!/bin/sh

echo "=== 1. Load module counter ==="
insmod counter_driver.ko || exit 1

echo "=== 2. Kiem tra /proc/counter_info ban dau ==="
cat /proc/counter_info

echo "=== 3. Doc tu /dev/counter (Auto-increment) ==="
cat /dev/counter
cat /dev/counter

echo "=== 4. Ghi gia tri moi (vi du: 100) vao /dev/counter ==="
echo "100" > /dev/counter
cat /dev/counter

echo "=== 5. Reset ve 0 ==="
echo "0" > /dev/counter
cat /proc/counter_info

echo "=== 6. Unload module ==="
rmmod counter_driver
echo "=== Hoan tat test Task 2 ==="
