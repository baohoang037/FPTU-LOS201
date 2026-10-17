# FPT University - Linux and Open Source Platform (LOS201)

[![Linux Kernel](https://img.shields.io/badge/Kernel-5.15.0%20LTS-blue.svg?logo=linux&logoColor=white)](https://kernel.org)
[![Target Arch](https://img.shields.io/badge/Architecture-ARMv7--A%20Cortex--A9-orange.svg)](https://developer.arm.com)
[![Platform](https://img.shields.io/badge/Emulator-QEMU%20vexpress--a9-green.svg)](https://www.qemu.org)
[![Language](https://img.shields.io/badge/Language-C%20%7C%20Bash%20%7C%20Makefile-yellow.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

This repository contains all experimental deliverables, kernel source modifications, driver implementations, configurations, and formal technical reports for **Linux and Open Source Platform (LOS201)** at **FPT University - Ho Chi Minh City Campus**.

---

## 👥 Engineering Team Members

| Full Name | Roll Number | Engineering Role |
| :--- | :---: | :--- |
| **Hoàng Ngọc Gia Bão** | **SE203238** | System Architect, Driver & Real-Time Specialist |
| **Trần Hồ Khánh Tân** | **SE203740** | Kernel Driver & ProcFS Subsystem |
| **Nguyễn Trọng Hùng** | **SE204352** | IPC, POSIX Message Queues & Logging Daemon |
| **Nguyễn Quế Vũ** | **SE204290** | Memory Management & Valgrind Auditing |
| **Nguyễn Việt Anh** | **SE204364** | Profiling (strace, perf) & Benchmarking |
| **Hồ Phan Anh Tuấn** | **SE203437** | Dynamic Debugging (GDB) & Technical Documentation |

- **Supervising Lecturer:** Mr. Phạm Thế Vinh

---

## 📂 Repository Structure

- **`lab01_kernel_boot/`**: Linux Kernel Configuration & System Boot on ARMv7 Architecture.
  * `configs/`: Linux Kernel and BusyBox configuration files (`kernel.config`, `busybox.config`).
  * `rootfs/`: Minimal BusyBox-based initramfs root filesystem used for the ARMv7 Linux boot process.
    * `initramfs/`: Root filesystem containing system initialization scripts, runtime mount points, and BusyBox userspace directories.
      * `etc/`: System initialization configuration including `inittab` and `init.d/rcS`.
      * `dev/`, `proc/`, `sys/`: Device and virtual filesystem mount points used during system startup.
      * `bin/`, `sbin/`, `usr/bin/`, `usr/sbin/`: Userspace executable directories.
  * `output/`: Generated boot artifacts including Linux kernel image (`zImage`), Device Tree Blob (`vexpress-v2p-ca9.dtb`), and compressed initramfs image (`initramfs.cpio.gz`).
  * `report/`: Formal technical PDF laboratory report (`Lab01.pdf`).
- **`lab02_device_driver/`**: Writing Character Device Drivers & Flash Filesystem Management.
  * `driver/`: Kernel module source (`lab2_driver.c`), `Makefile`, and compiled ARM binary (`lab2_driver.ko`).
  * `rootfs/`: BusyBox initialization scripts (`inittab`, `rcS`) and userspace validation suites (`test_driver.sh`, `test_procfs.sh`).
  * `logs/`: Verifiable raw execution terminal logs (`boot_log.txt`, `driver_test.txt`, `procfs_test.txt`, `mtd_jffs2.txt`).
  * `docs/`: Architectural schematics and system design diagrams.
  * `report/`: Formal technical PDF laboratory report (`SE203238_Lab02_BaoCao.pdf`).
- **`lab03_open_source/`**: Open Source Development Workflow & Community Contribution.
- **`assignment01/`**: Advanced Linux Architecture & System Programming (IOCTL & Misc Device).
  * `task1_ioctl/`: Source code for extending the LAB-02 character device driver with four IOCTL commands.
  * `task2_misc/`: Source code for implementing a counter device using the Linux miscellaneous device framework.
  * `logs/`: Test outputs and kernel logs.
  * `docs/`: Driver architecture diagrams and supporting documentation.
  * `report/`: Final technical report in PDF format (`Asgn01.pdf`).
- **`assignment02_sensor_monitoring/`**: Capstone Project – Real-Time Multi-Threaded Sensor Monitoring System (SMS).
  * `driver/`: Kernel character device driver simulating sensor hardware (`sms_sensor_driver.c`, `sms_sensor.h`, `Makefile`, `sms_sensor_driver.ko`).
  * `app/`: Multi-threaded POSIX real-time application source (`sms_app.c`, `circular_buffer.c`, `test_circular_buffer.c`, worker threads, `measure_memory.sh`, `sms_app`, `sms_app_x86`).
  * `output/`: Bootable system artifacts (`initramfs_asgn2.cpio.gz`).
  * `logs/`: Verifiable runtime execution, memory footprint, and profiling logs (`perf_sms.txt`, `strace_sms.txt`, `valgrind_sms.txt`, `proc_sms_maps.txt`, `jitter_report.txt`, `sms.log`, etc.).
  * `docs/`: System architecture diagram, finite state machine diagram, and 13 experimental verification screenshots (`01_` to `13_`).
  * `report/`: Formal technical engineering report in PDF format (`assignment 2.pdf`).
- **`.gitignore`**: High-performance Git filter excluding raw multi-gigabyte kernel build trees and object artifacts.

---

## 🔬 Lab 01: Linux Kernel Configuration & System Boot on ARMv7

### 1. Architectural Overview & System Flow

LAB 01 focuses on configuring, building, and booting an Embedded Linux system for the ARMv7-A Cortex-A9 architecture using QEMU `vexpress-a9`.

The complete boot flow consists of Linux Kernel configuration and cross-compilation, U-Boot bootloader preparation, BusyBox root filesystem construction, initramfs packaging, and final Linux system boot on QEMU.

<img width="341" height="197" alt="image" src="https://github.com/user-attachments/assets/723a2bff-1f18-4bc8-b4ec-36f4b4209d71" />

### 2. Comprehensive Technical Highlights

- **Linux Kernel Configuration & Cross-Compilation:**
  * Configured Linux Kernel `5.15.0 LTS` for the ARMv7-A Cortex-A9 platform.
  * Used the `arm-linux-gnueabihf-` cross-compilation toolchain to build the kernel for ARM.
  * Started from the `vexpress_defconfig` configuration for the QEMU Versatile Express platform.
  * Enabled the required kernel features for initramfs support and the PL011 UART serial console.
  * Generated the ARM kernel image `zImage` and the Device Tree Blob `vexpress-v2p-ca9.dtb`.

- **U-Boot Bootloader:**
  * Configured U-Boot for the `vexpress_ca9x4` platform.
  * Built and executed U-Boot on the QEMU `vexpress-a9` machine.
  * Inspected the U-Boot version, board information, and environment variables.
  * Configured the Linux kernel boot arguments and `bootcmd` using the `bootz` command.

- **BusyBox & Minimal Root Filesystem:**
  * Built BusyBox as a statically linked ARMv7 userspace environment.
  * Created a minimal initramfs root filesystem for the embedded Linux system.
  * Prepared the required directory structure including `/bin`, `/sbin`, `/usr/bin`, `/usr/sbin`, `/dev`, `/proc`, `/sys`, `/tmp`, `/etc`, and `/lib`.
  * Implemented `/init`, `/etc/inittab`, and `/etc/init.d/rcS` for system initialization.
  * Configured the root filesystem to provide a minimal BusyBox-based userspace environment.

- **Linux Boot & Initramfs Integration:**
  * Packaged the BusyBox root filesystem into `initramfs.cpio.gz`.
  * Booted the Linux kernel on QEMU `vexpress-a9` using the kernel image, Device Tree Blob, and initramfs.
  * Configured the kernel command line with the `ttyAMA0` serial console and `/sbin/init`.
  * Verified the transition from the Linux kernel to the BusyBox userspace shell.

---

## 🔬 Lab 02: Writing Device Drivers & File System Management

### 1. Architectural Overview & System Flow
The driver bridges userspace system call requests with physical/emulated hardware resources while strictly maintaining kernel space isolation and data integrity.

![Architecture Diagram](lab02_device_driver/docs/architecture_diagram.png)

### 2. Comprehensive Technical Highlights
- **Kernel Character Device Driver Subsystem:**
  * **Major/Minor Allocation:** Dynamically bound to Major number `240` (reserved for local/experimental use) and Minor `0` mapped to device special node `/dev/lab2`.
  * **POSIX File Operations (`fops`):** Implemented handlers for `open`, `release`, `read`, and `write` system calls.
  * **Zero-Panic Memory Safety:** Data transfers between userspace and kernel space are strictly handled via `copy_from_user()` and `copy_to_user()`.
  * **Concurrency & Race Condition Prevention:** All critical sections accessing the 1024-byte `device_buffer` and tracking variables (`buffer_len`, `open_count`) are serialized via `DEFINE_MUTEX(lab2_mutex)`.

- **Diagnostic & Export Virtual Filesystems:**
  * **procfs (`/proc/lab2_info`):** Integrated via the `seq_file` interface and `single_open()` helper to provide formatted, multi-line diagnostic summaries.
  * **sysfs (`/sys/class/lab2_class/lab2/`):** Decomposed internal driver variables into discrete, atomic, read-only attributes (`buffer_len`, `open_count`, `last_data`) utilizing the `DEVICE_ATTR_RO` macro.

- **Memory Technology Device (MTD) & JFFS2 Subsystem:**
  * **Flash Hardware Simulation:** Emulated a 32MB physical NAND flash profile with 512-byte page size and 16KB eraseblock geometry (`0x4000`) using `nandsim`.
  * **Verified Persistence:** Validated runtime writes, appending data, and verified full data retention across unmount and remount cycles on `/dev/mtdblock1`.

---

## 🔬 Assignment 01 – How to Write a Device Driver

### 1. Overview
This assignment focuses on Linux device driver development in an embedded Linux environment. It consists of two tasks: extending a character device driver with IOCTL commands and implementing a counter driver using the Linux miscellaneous device framework.

<img width="375" height="343" alt="image" src="https://github.com/user-attachments/assets/c28b2057-6f8a-47a7-99a8-bc6bc822ff66" />

### 2. Objectives & Task Breakdown
- **Task 1 – Extend a Character Device Driver with IOCTL:** Implemented 4 IOCTL commands (`Reset Buffer`, `Get Statistics`, `Set Mode`, `Get Version`).
- **Task 2 – Implement a Counter Driver:** Implemented an autonomous counting device using the Linux `miscdevice` framework.

### 3. Project Structure

```text
assignment01/
├── task1_ioctl/
│   ├── asgn1_driver.c
│   ├── asgn1_ioctl.h
│   ├── Makefile
│   ├── asgn1_user.c
│   └── test_asgn1.sh
├── task2_misc/
│   ├── counter_driver.c
│   ├── Makefile
│   ├── counter_driver.mod
│   ├── counter_driver.mod.c
│   ├── counter_driver.mod.o
│   ├── counter_driver.o
│   └── test.sh
│   ├── Module.symvers
│   └── modules.order
└── report/
    └── Asgn01.pdf
```

---

## 🔬 Assignment 02 – Sensor Monitoring System (SMS)

### 1. Architectural Overview & System Flow
The Sensor Monitoring System (SMS) is an end-to-end, multi-threaded real-time embedded Linux monitoring suite. It samples simulated environmental sensor hardware via a dedicated kernel character driver, buffers samples safely across asynchronous producer-consumer boundaries using a thread-safe ring buffer, processes threshold alerts, and dispatches data across POSIX IPC pipelines.

#### System Architecture & IPC Data Flow
![SMS Architecture Diagram](assignment02_sensor_monitoring/docs/architecture_diagram.png)

#### Finite State Machine (FSM) Lifecycle
![SMS State Machine](assignment02_sensor_monitoring/docs/state_machine_diagram.png)

---

### 2. Task-by-Task Implementation Summary & Technical Evaluation

#### 📌 Task 1: Architecture & Multi-Threaded Application Implementation (30 pts)
- **Kernel Character Driver Subsystem (`sms_sensor_driver.ko`):**
  * Registers dynamic character device `/dev/sms_sensor` implementing `open()`, `read()`, `llseek()`, and `release()`.
  * Emits formatted CSV sample strings: `<timestamp_ms>,<temperature>,<humidity>\n`.
  * Implements defensive hardware rate-limiting (`g_min_interval_ms = 100ms`), returning `-EAGAIN` upon rapid calls to prevent bus flooding.
  * Supports runtime configuration via `ioctl(SMS_SET_INTERVAL)` and exports cumulative telemetry to `/proc/sms_stats`.
- **Thread-Safe Circular Ring Buffer:**
  * Fixed capacity of 64 slots allocated once on heap; synchronized via `pthread_mutex_t` and dual condition variables (`not_empty`, `not_full`).
  * Implements non-blocking drop-on-full semantics: increments `overflow_count` rather than stalling producer threads to preserve real-time sampling deadlines.
- **POSIX Multi-Threading Pipeline & Message Queues:**
  * **Sensor Thread:** Periodically samples `/dev/sms_sensor` every 500ms using `clock_nanosleep(CLOCK_MONOTONIC)`.
  * **Processor Thread:** Calculates 10-sample rolling averages, evaluates threshold violations (Temp > 40°C, Humid > 80%, Spike > 5°C), and dispatches messages via `mq_timedsend()` (50ms timeout).
  * **Logger & Alert Workers:** Dedicated consumers handling file persistence (`/tmp/sms.log` with 1MB log rotation and 5s periodic flushing) and instant high-priority console alerting (`stderr`).

#### 📌 Task 2: Memory Management & Driver Integration Audit (20 pts)
- **Valgrind Memcheck Verification:** 0 bytes definitely lost, 0 bytes indirectly lost, 0 bytes possibly lost, and 0 errors. All allocated memory and POSIX queue handles are cleanly released on SIGINT.
- **Memory Footprint Tracking (`/proc/[PID]/status`):**
  * Evaluated across 3 distinct checkpoints: T=5s (Init: VmRSS=2,752 kB), T=30s (Steady: VmRSS=2,884 kB), T=55s (Pre-exit: VmRSS=2,888 kB). Demonstrates absolute curve flattening (<0.14% variation) confirming zero heap fragmentation.
- **Virtual Memory Segmentation (`/proc/[PID]/maps`):** Verified discrete separation of Text, Data/BSS, Heap, and dedicated ~8MB stack allocations per worker thread with protective guard pages.

#### 📌 Task 3: Profiling, Tracing & Interactive GDB Debugging (20 pts)
- **System Call Profiling (`strace -c`):** Top 5 syscalls dominated by `clock_nanosleep` (37.79%), `mq_timedreceive` (36.85%), and `futex` (17.58%), confirming an event-driven, I/O-bound architecture with zero CPU waste on polling.
- **CPU Hotspot Call-Graph (`perf report`):** Resolved kernel symbols with `kptr_restrict=0`; 60.15% execution overhead concentrated in kernel waitqueues (`__x64_sys_mq_timedreceive` -> `schedule_hrtimeout_range_clock`).
- **Interactive Multi-Thread Debugging (`GDB Scenario B`):** Breakpoint set at `processor_thread.c:79`, state audited with `info threads`, and threshold alerting validated via variable injection (`set var sample.temperature = 45.0`).

#### 📌 Task 4: Real-Time Determinism & ARM Portability (15 pts)
- **Real-Time Jitter Quantification (`SCHED_FIFO` vs `SCHED_OTHER`):**
  * Max Jitter reduced from 2,601 μs (2.6 ms) down to 285 μs (0.28 ms) — **89.1% latency reduction**.
  * Physical RAM locking via `mlockall(MCL_CURRENT | MCL_FUTURE)` eliminated page fault latency spikes.
- **ARMv7-A Cross-Compilation:**
  * Clean build using `arm-linux-gnueabihf-gcc`.
  * Verified binary: `ELF 32-bit LSB pie executable, ARM, EABI5 version 1 (SYSV)`.
  * Enforced cross-architecture 64-bit portability using explicit `(unsigned long long)` casting and `%llu` specifiers.

#### 📌 Task 5: Technical Report, Synchronization Proof & Demo (15 pts)
- **Formal Technical Report:** Complete engineering documentation (`report/assignment 2.pdf`) covering architectural decisions, thread synchronization proofs, Coffman deadlock elimination, empirical benchmarks, and student reflection.
- **Video Demonstration:** 3–5 minute comprehensive screencast showcasing driver insertion, verbose execution, live alert triggering, log verification, and graceful shutdown.

---

### 3. Step-by-Step Reproduction Guide (How to Run)

#### Step 1: Build Driver & Userspace Applications
```bash
# 1. Compile Kernel Driver (sms_sensor_driver.ko)
cd assignment02_sensor_monitoring/driver
make clean && make

# 2. Compile Userspace Daemon (x86_64 Host and ARMv7 Target)
cd ../app
make clean
make host    # Generates sms_app_x86 for local profiling
make arm     # Generates sms_app for ARMv7 target deployment

# 3. Compile and Run Unit Test Suite
gcc -Wall -Wextra -pthread test_circular_buffer.c circular_buffer.c -o test_cb
./test_cb
```

#### Step 2: Load Driver & Verify Device Nodes
```bash
# Insert simulated sensor driver into the kernel
sudo insmod ../driver/sms_sensor_driver.ko

# Verify character device node and procfs diagnostic entries
ls -l /dev/sms_sensor
cat /proc/sms_stats
```

#### Step 3: Run Sensor Monitoring System
```bash
# Run with 500ms interval, 40°C temp threshold, 80% humidity, 60s duration, and verbose output
sudo ./sms_app_x86 -i 500 -t 40.0 -h 80.0 -d 60 -v

# Run with Real-Time Scheduling (SCHED_FIFO Priority 50 + mlockall)
sudo ./sms_app_x86 -i 500 -d 60 -r
```

#### Step 4: Verify Profiling and Diagnostics
```bash
# 1. Run Dynamic Memory Leak Audit (Valgrind)
valgrind --leak-check=full --show-leak-kinds=all ./sms_app_x86 -d 30

# 2. Trace Cumulative System Calls (strace)
strace -c ./sms_app_x86 -d 30

# 3. Record and Analyze CPU Hotspots (perf)
sudo perf record -g ./sms_app_x86 -d 30
sudo perf report --stdio
```

#### Step 5: Unload Driver & Packaging for LMS Submission
```bash
# Unload kernel module cleanly
sudo rmmod sms_sensor_driver

# Package workspace into the required .tar.gz archive
tar -czvf SE203238_HoangNgocGiaBao_Asgn02.tar.gz assignment02_sensor_monitoring/
```

---

### 4. Complete Project Deliverables Tree

```text
assignment02_sensor_monitoring/
├── driver/
│   ├── sms_sensor_driver.c
│   ├── sms_sensor.h
│   ├── Makefile
│   └── sms_sensor_driver.ko
├── app/
│   ├── sms_app.c
│   ├── sms_sensor.h
│   ├── circular_buffer.h
│   ├── circular_buffer.c
│   ├── test_circular_buffer.c
│   ├── sensor_thread.h
│   ├── sensor_thread.c
│   ├── processor_thread.h
│   ├── processor_thread.c
│   ├── logger_thread.h
│   ├── logger_thread.c
│   ├── alert_thread.h
│   ├── alert_thread.c
│   ├── measure_memory.sh
│   ├── Makefile
│   ├── sms_app
│   └── sms_app_x86
├── output/
│   └── initramfs_asgn2.cpio.gz
├── logs/
│   ├── perf_sms.txt
│   ├── proc_sms_maps.txt
│   ├── proc_sms_stats_after.txt
│   ├── proc_sms_stats_before.txt
│   ├── proc_sms_stats_runtime.txt
│   ├── sms_sample_run.txt
│   ├── strace_sms.txt
│   ├── valgrind_sms.txt
│   ├── jitter_report.txt
│   └── sms.log
├── docs/
│   ├── architecture_diagram.png
│   ├── state_machine_diagram.png
│   ├── 01_project_structure.png
│   ├── 02_driver_build.png
│   ├── 03_driver_test.png
│   ├── 04_circular_buffer_test.png
│   ├── 05_multithread_app_run.png
│   ├── 06_sms_log_output.png
│   ├── 07_valgrind_clean.png
│   ├── 08_memory_analysis.png
│   ├── 09_strace_summary.png
│   ├── 10_perf_report.png
│   ├── 11_gdb_debug_session.png
│   ├── 12_jitter_rt_report.png
│   └── 13_cross_compile_arm.png
└── report/
    └── assignment 2.pdf
```

---

## 🛠️ Team Collaboration Protocol

1. **Keep `main` Clean:** All direct commits to `main` are restricted. Work is conducted on branches (`feature/<name>` or `docs/<name>`).
2. **Pull Before Work:** Always execute `git pull origin main` prior to modifying any shared markdown documentation or configuration files.
3. **Pull Request Verification:** Submit changes through GitHub Pull Requests with descriptive summaries and verified test outputs.
