#!/bin/sh
# test_asgn1.sh - chạy bên trong QEMU (busybox initramfs)

MODULE=/lib/modules/asgn1_driver.ko
MODNAME=asgn1_driver
DEV=/dev/asgn1
MAJOR=241
HELPER=/bin/asgn1_user
PASS=0
FAIL=0

check() {
    if [ "$2" = "$3" ]; then
        echo "  [PASS] $1"
        PASS=$((PASS + 1))
    else
        echo "  [FAIL] $1 (thực tế='$2', kỳ vọng='$3')"
        FAIL=$((FAIL + 1))
    fi
}

stat_field() {
    $HELPER $DEV stats | grep "^$1=" | cut -d= -f2
}

echo "=== [1] Load module & tạo /dev/asgn1 (major $MAJOR) ==="
insmod $MODULE major_num=$MAJOR || { echo "insmod thất bại"; exit 1; }
rm -f $DEV
mknod $DEV c $MAJOR 0 || { echo "mknod thất bại"; exit 1; }
chmod 666 $DEV
check "module đã load" "$(grep -c "^$MODNAME " /proc/modules)" "1"
check "mode mặc định là ECHO (1)" "$(stat_field mode)" "1"

echo "=== [2] Kiểm tra ECHO mode ==="
echo -n "hello" > $DEV
check "ECHO: ghi 'hello', đọc lại" "$(cat $DEV)" "hello"

echo "=== [3] Kiểm tra KERNEL mode ==="
$HELPER $DEV mode 0 > /dev/null
echo -n "world" > $DEV
check "KERNEL: đọc lại có tiền tố [KERNEL]" "$(cat $DEV)" "[KERNEL] world"

$HELPER $DEV mode 1 > /dev/null
echo -n "back" > $DEV
check "Trở về ECHO: không có tiền tố" "$(cat $DEV)" "back"

echo "=== [4] GET_STATS ==="
$HELPER $DEV stats
check "write_count = 3" "$(stat_field write_count)" "3"
check "last_write_size = 4" "$(stat_field last_write_size)" "4"
check "buffer_len = 4" "$(stat_field buffer_len)" "4"

echo "=== [5] GET_VERSION ==="
VER=$($HELPER $DEV version)
echo "  version: $VER"
check "chuỗi version đúng" "$VER" "asgn1_driver v1.0 - SE203437"

echo "=== [6] RESET_BUFFER ==="
echo -n "data to be reset" > $DEV
$HELPER $DEV reset > /dev/null
check "RESET: write_count = 0" "$(stat_field write_count)" "0"
check "RESET: read_count = 0" "$(stat_field read_count)" "0"
check "RESET: buffer_len = 0" "$(stat_field buffer_len)" "0"
check "RESET: cat trả về chuỗi rỗng" "$(cat $DEV)" ""

echo "=== [7] Lệnh không hợp lệ & mode sai ==="
check "ioctl không tồn tại -> ENOTTY (25)" \
    "$($HELPER $DEV invalid | grep -o 'errno=[0-9]*')" "errno=25"
check "SET_MODE=5 -> EINVAL (22)" \
    "$($HELPER $DEV mode 5 | grep -o 'errno=[0-9]*')" "errno=22"

echo "=== [8] Unload & kiểm tra cleanup ==="
rm -f $DEV
rmmod $MODNAME || { echo "  rmmod thất bại"; FAIL=$((FAIL + 1)); }
check "module đã gỡ" "$(grep -c "^$MODNAME " /proc/modules)" "0"
echo "--- dmesg (asgn1) ---"
dmesg | grep asgn1 | tail -n 10
check "dmesg xác nhận cleanup" \
    "$(dmesg | grep -q 'cleanup done' && echo yes)" "yes"

echo "=== KẾT QUẢ: $PASS passed, $FAIL failed ==="
[ $FAIL -eq 0 ]
