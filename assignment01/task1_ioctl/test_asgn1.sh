#!/bin/sh

echo "================================"
echo " Assignment 1 - Task 1 Test"
echo "================================"

if [ ! -e /dev/asgn1 ]; then
    echo "[ERROR] /dev/asgn1 not found"
    exit 1
fi

if [ ! -x /root/ioctl_test ]; then
    echo "[ERROR] ioctl_test not found"
    exit 1
fi

/root/ioctl_test
result=$?

echo "================================"

if [ "$result" -eq 0 ]; then
    echo "TASK 1: ALL TESTS PASSED"
else
    echo "TASK 1: TEST FAILED"
fi

exit "$result"
