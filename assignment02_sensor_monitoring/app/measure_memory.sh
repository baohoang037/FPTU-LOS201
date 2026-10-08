#!/bin/bash
set -e

# Đảm bảo driver đang chạy
sudo chmod 666 /dev/sms_sensor

echo "=== 1. CAPTURE /proc/sms_stats TRƯỚC KHI CHẠY ==="
cat /proc/sms_stats | tee ../logs/proc_sms_stats_before.txt

echo -e "\n=== 2. KHỞI CHẠY sms_app_x86 TRONG 60 GIÂY (INTERVAL 500ms) ==="
./sms_app_x86 -i 500 -d 60 > ../logs/sms_sample_run.txt 2>&1 &
APP_PID=$!
echo "App running with PID: $APP_PID"

echo -e "\n=== 3. THU THẬP VmSize & VmRSS TẠI T=5s, T=30s, T=55s ==="

sleep 5
echo "--- [T=5s] ---" | tee -a ../logs/proc_sms_stats_runtime.txt
grep -E 'VmSize|VmRSS' /proc/$APP_PID/status | tee -a ../logs/proc_sms_stats_runtime.txt
cat /proc/$APP_PID/maps > ../logs/proc_sms_maps.txt

sleep 25
echo "--- [T=30s] ---" | tee -a ../logs/proc_sms_stats_runtime.txt
grep -E 'VmSize|VmRSS' /proc/$APP_PID/status | tee -a ../logs/proc_sms_stats_runtime.txt

sleep 25
echo "--- [T=55s] ---" | tee -a ../logs/proc_sms_stats_runtime.txt
grep -E 'VmSize|VmRSS' /proc/$APP_PID/status | tee -a ../logs/proc_sms_stats_runtime.txt

# Chờ ứng dụng kết thúc
wait $APP_PID 2>/dev/null || true

echo -e "\n=== 4. CAPTURE /proc/sms_stats SAU KHI CHẠY 60s ==="
cat /proc/sms_stats | tee ../logs/proc_sms_stats_after.txt

echo -e "\n=== HOÀN TẤT ĐO ĐẠC TASK 2 ==="
