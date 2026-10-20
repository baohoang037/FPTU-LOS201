# FPT University - Linux and Open Source Platform (LOS201)

[![Linux Kernel](https://img.shields.io/badge/Kernel-5.15.0%20LTS-blue.svg?logo=linux&logoColor=white)](https://kernel.org)
[![Target Arch](https://img.shields.io/badge/Architecture-ARMv7--A%20Cortex--A9-orange.svg)](https://developer.arm.com)
[![Platform](https://img.shields.io/badge/Emulator-QEMU%20vexpress--a9-green.svg)](https://www.qemu.org)
[![Language](https://img.shields.io/badge/Language-C%20%7C%20Bash%20%7C%20Makefile-yellow.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

This repository contains all experimental deliverables, kernel source modifications, driver implementations, configurations, and formal technical reports for **Linux and Open Source Platform (LOS201)** at **FPT University - Ho Chi Minh City Campus**.

---

## 👥 Engineering Team Members

| Full Name | Roll Number |
| :--- | :---: |
| **Hoàng Ngọc Gia Bão** | **SE203238** |
| **Trần Hồ Khánh Tân** | **SE203740** |
| **Nguyễn Trọng Hùng** | **SE204352** |
| **Nguyễn Quế Vũ** | **SE204290** |
| **Nguyễn Việt Anh** | **SE204364** |
| **Hồ Phan Anh Tuấn** | **SE203437** |

- **Supervising Lecturer:** Mr. Phạm Thế Vinh

---

## 📂 Repository Structure

> *Click on any folder or file name below to navigate directly to its contents on GitHub.*

- [`lab01_kernel_boot/`](./lab01_kernel_boot/): Linux Kernel Configuration & System Boot on ARMv7 Architecture.
  * [`configs/`](./lab01_kernel_boot/configs/): Kernel and BusyBox build configurations ([`kernel.config`](./lab01_kernel_boot/configs/kernel.config), [`busybox.config`](./lab01_kernel_boot/configs/busybox.config)).
  * [`rootfs/`](./lab01_kernel_boot/rootfs/): Minimal BusyBox-based root filesystem and startup scripts ([`initramfs/etc/inittab`](./lab01_kernel_boot/rootfs/initramfs/etc/inittab), [`init.d/rcS`](./lab01_kernel_boot/rootfs/initramfs/etc/init.d/rcS)).
  * [`output/`](./lab01_kernel_boot/output/): Generated ARM boot artifacts ([`zImage`](./lab01_kernel_boot/output/zImage), [`vexpress-v2p-ca9.dtb`](./lab01_kernel_boot/output/vexpress-v2p-ca9.dtb), [`initramfs.cpio.gz`](./lab01_kernel_boot/output/initramfs.cpio.gz)).
  * [`report/`](./lab01_kernel_boot/report/): Formal technical PDF laboratory report ([`Lab01.pdf`](./lab01_kernel_boot/report/Lab01.pdf)).

- [`lab02_device_driver/`](./lab02_device_driver/): Writing Character Device Drivers & Flash Filesystem Management.
  * [`driver/`](./lab02_device_driver/driver/): Kernel module source and compiled binary ([`lab2_driver.c`](./lab02_device_driver/driver/lab2_driver.c), [`lab2_driver.ko`](./lab02_device_driver/driver/lab2_driver.ko), [`Makefile`](./lab02_device_driver/driver/Makefile)).
  * [`rootfs/`](./lab02_device_driver/rootfs/): Validation shell scripts ([`test_driver.sh`](./lab02_device_driver/rootfs/test_driver.sh), [`test_procfs.sh`](./lab02_device_driver/rootfs/test_procfs.sh)).
  * [`logs/`](./lab02_device_driver/logs/): Execution terminal outputs ([`boot_log.txt`](./lab02_device_driver/logs/boot_log.txt), [`driver_test.txt`](./lab02_device_driver/logs/driver_test.txt), [`mtd_jffs2.txt`](./lab02_device_driver/logs/mtd_jffs2.txt)).
  * [`docs/`](./lab02_device_driver/docs/): Architectural diagrams ([`architecture_diagram.png`](./lab02_device_driver/docs/architecture_diagram.png)).
  * [`report/`](./lab02_device_driver/report/): Formal technical PDF laboratory report ([`lab 2.pdf`](./lab02_device_driver/report/lab%202.pdf)).

- [`lab03_open_source/`](./lab03_open_source/): Open Source Development Workflow & Community Contribution.

- [`assignment01/`](./assignment01/): Advanced Linux Architecture & System Programming (IOCTL & Misc Device).
  * [`task1_ioctl/`](./assignment01/task1_ioctl/): Extended character driver implementing 4 IOCTL commands ([`asgn1_driver.c`](./assignment01/task1_ioctl/asgn1_driver.c), [`asgn1_ioctl.h`](./assignment01/task1_ioctl/asgn1_ioctl.h), [`test_asgn1.sh`](./assignment01/task1_ioctl/test_asgn1.sh)).
  * [`task2_misc/`](./assignment01/task2_misc/): Miscellaneous device counter driver ([`counter_driver.c`](./assignment01/task2_misc/counter_driver.c), [`test.sh`](./assignment01/task2_misc/test.sh)).
  * [`report/`](./assignment01/report/): Final technical report in PDF format ([`Asgn01.pdf`](./assignment01/report/Asgn01.pdf)).

- [`assignment02_sensor_monitoring/`](./assignment02_sensor_monitoring/): Capstone Project – Real-Time Multi-Threaded Sensor Monitoring System (SMS).
  * [`driver/`](./assignment02_sensor_monitoring/driver/): Kernel character driver simulating environmental sensors ([`sms_sensor_driver.c`](./assignment02_sensor_monitoring/driver/sms_sensor_driver.c), [`sms_sensor_driver.ko`](./assignment02_sensor_monitoring/driver/sms_sensor_driver.ko)).
  * [`app/`](./assignment02_sensor_monitoring/app/): Multi-threaded daemon source ([`sms_app.c`](./assignment02_sensor_monitoring/app/sms_app.c), [`circular_buffer.c`](./assignment02_sensor_monitoring/app/circular_buffer.c), [`measure_memory.sh`](./assignment02_sensor_monitoring/app/measure_memory.sh)).
  * [`output/`](./assignment02_sensor_monitoring/output/): Standalone boot image ([`initramfs_asgn2.cpio.gz`](./assignment02_sensor_monitoring/output/initramfs_asgn2.cpio.gz)).
  * [`logs/`](./assignment02_sensor_monitoring/logs/): 8 verifiable runtime logs ([`perf_sms.txt`](./assignment02_sensor_monitoring/logs/perf_sms.txt), [`strace_sms.txt`](./assignment02_sensor_monitoring/logs/strace_sms.txt), [`valgrind_sms.txt`](./assignment02_sensor_monitoring/logs/valgrind_sms.txt), etc.).
  * [`docs/`](./assignment02_sensor_monitoring/docs/): Engineering diagrams ([`architecture_diagram.png?v=2`](./assignment02_sensor_monitoring/docs/architecture_diagram.png?v=2), [`state_machine_diagram.png?v=2`](./assignment02_sensor_monitoring/docs/state_machine_diagram.png?v=2), screenshots `01_` to `13_`).
  * [`report/`](./assignment02_sensor_monitoring/report/): Academic engineering PDF report ([`assignment 2.pdf`](./assignment02_sensor_monitoring/report/assignment%202.pdf)).

---

## 🔬 Lab 01: Linux Kernel Configuration & System Boot on ARMv7

### 1. Architectural Overview & System Flow

LAB 01 focuses on configuring, building, and booting an Embedded Linux system for the ARMv7-A Cortex-A9 architecture using QEMU `vexpress-a9`. The boot flow consists of kernel cross-compilation, U-Boot bootloader preparation, BusyBox rootfs packaging, and boot verification.

<img width="341" height="197" alt="Lab 01 Boot Flow" src="https://github.com/user-attachments/assets/723a2bff-1f18-4bc8-b4ec-36f4b4209d71" />

### 2. Comprehensive Technical Highlights
- **Cross-Compilation:** Linux Kernel `5.15.0 LTS` built with `arm-linux-gnueabihf-` using `vexpress_defconfig`.
- **Bootloader & Userspace:** Statically compiled BusyBox rootfs packaged into [`initramfs.cpio.gz`](./lab01_kernel_boot/output/initramfs.cpio.gz), loaded via U-Boot on `ttyAMA0`.
- **System Verification:** Verified active CPU topology via `/proc/cpuinfo`, memory layout via `/proc/meminfo`, and active mount points.

---

## 🔬 Lab 02: Writing Device Drivers & File System Management

**Embedded Linux Systems (LOS201) · FPT University – Ho Chi Minh City Campus · Lecturer: Phạm Thế Vinh**

> `Character Device Driver | Mutex Concurrency | ProcFS & Sysfs Telemetry | MTD Flash & JFFS2`

### 1. Architectural Overview & Data Flow
Bridges userspace system call requests (`open`, `read`, `write`, `close`) with simulated hardware resources while maintaining strict kernel-space memory isolation and data integrity.

![Lab 02 Architecture Diagram](./lab02_device_driver/docs/architecture_diagram.png)

---

### 2. Implementation Tasks & Technical Evaluation

#### 📌 Task 1: Character Driver Core & Synchronization (Major 240, Minor 0)
- **Device Registration ([`lab2_driver.c`](./lab02_device_driver/driver/lab2_driver.c)):** Registered character device node at Major number `240`, Minor `0` via `register_chrdev()`. Automated dynamic device node creation at [`/dev/lab2`](./lab02_device_driver/driver/lab2_driver.c) using `class_create()` (`lab2_class`) and `device_create()`.
- **Memory Safety & Isolation:** Zero-panic memory transfers between user and kernel spaces using `copy_to_user()` and `copy_from_user()`. Converted user pointers safely while rejecting unmapped regions with `-EFAULT`.
- **Concurrency & Race Condition Prevention:** Serialized read and write critical sections on `device_buffer` using `DEFINE_MUTEX(lab2_mutex)`, completely eliminating multi-process race conditions.
- **Command Dispatch & Buffer Boundary Protection:**
  * **Command `clear`:** Sending `echo "clear" > /dev/lab2` resets buffer length (`buffer_len = 0`) and flushes storage, leaving `cat /dev/lab2` cleanly empty.
  * **128-Byte Write Truncation:** Inputs exceeding 128 bytes are truncated to 128 bytes while consuming full stream tokens (`return orig_len`), preventing re-entrancy write loops in user space.

| Test Operation | Execution Command | Observed System State | Evaluation Verdict |
| :--- | :--- | :--- | :---: |
| **Driver Module Insertion** | `insmod /lab2_driver.ko` | Node `/dev/lab2` created (crw-------, major 240) | ✅ PASS |
| **Standard Write & Read** | `echo "FPTU IC Design" > /dev/lab2` | `cat /dev/lab2` returns "FPTU IC Design" | ✅ PASS |
| **Command `clear` Reset** | `echo "clear" > /dev/lab2` | Buffer flushed (`buffer_len = 0`), read returns empty | ✅ PASS |
| **Truncate to 128 Bytes** | `echo "<160 bytes>" > /dev/lab2` | `Data length: 128 bytes`, warning in `dmesg` | ✅ PASS |
| **Module Clean Unload** | `rmmod lab2_driver` | Resources unregistered, nodes cleaned from `/dev` | ✅ PASS |

---

#### 📌 Task 2: Kernel Telemetry & Diagnostics (ProcFS & Sysfs)
- **ProcFS Diagnostics ([`/proc/lab2_info`](./lab02_device_driver/rootfs/test_procfs.sh)):** Integrated `seq_file` interface to report dynamic statistics including Driver Name, Major Number, Allocated Buffer Size, Active Data Length, `Open count`, and cumulative `Write count`.
- **Granular Sysfs Attributes ([`/sys/class/lab2_class/lab2/`](./lab02_device_driver/driver/lab2_driver.c)):**
  * `read_count`: Total successful invocations of the `read()` syscall.
  * `buffer_size`: Static allocated buffer capacity (`1024 bytes`).
  * `buffer_len`: Real-time length of stored payload.
  * `status`: Dynamically outputs `EMPTY` (when `buffer_len == 0`) or `DATA` (when `buffer_len > 0`).
  * `total_bytes_read` & `total_bytes_written`: High-precision cumulative byte counters incremented strictly upon successful payload transactions.

| Sysfs / Procfs Node | Access Mode | Sample Value / Format | Technical Purpose |
| :--- | :---: | :---: | :--- |
| `/proc/lab2_info` | Read-Only | Text Key-Value Block | Comprehensive status snapshot via `seq_file` API |
| `/sys/.../status` | Read-Only | `EMPTY` / `DATA` | Binary state evaluation based on `buffer_len` |
| `/sys/.../buffer_size` | Read-Only | `1024` | Static allocated capacity of `device_buffer` |
| `/sys/.../buffer_len` | Read-Only | `0` to `128` | Exact active payload byte length |
| `/sys/.../read_count` | Read-Only | Unsigned integer | Frequency of `read()` system calls |
| `/sys/.../total_bytes_read` | Read-Only | Unsigned long | Cumulative count of bytes streamed to userspace |
| `/sys/.../total_bytes_written` | Read-Only | Unsigned long | Cumulative count of bytes written from userspace |

---

#### 📌 Task 3: Flash Storage & JFFS2 Filesystem Subsystem
- **NAND Flash Emulation:** Emulated physical NAND flash memory device (32MB) with `nandsim` (`first_id_byte=0x20`, `second_id_byte=0x76`).
- **JFFS2 Verification ([`mtd_jffs2.txt`](./lab02_device_driver/logs/mtd_jffs2.txt)):** Formatted and mounted partition to `/mnt/jffs2`. Verified flash persistence across system reboots and validated magic bitmask headers (`0x85 0x19`) on `/dev/mtdblock1`.

---

### 3. Step-by-Step Reproduction Guide (How to Run)

#### Step 1: Cross-Compile Driver & Package RootFS
```bash
# 1. Compile kernel module for ARM target architecture
cd lab02_device_driver/driver
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

# 2. Package module into initramfs and rebuild bootable cpio archive
~/embedded_lab2/build_and_pack.sh
```

#### Step 2: Boot QEMU & Load Driver
```bash
# 1. Launch QEMU ARM virtual platform
./run_qemu.sh

# 2. Inside QEMU guest (/ #), insert driver module
insmod /lab2_driver.ko

# 3. Verify device nodes and procfs registration
ls -l /dev/lab2
cat /proc/lab2_info
```

#### Step 3: Run Validation & Diagnostic Test Suite
```bash
# 1. Verify read/write transactions and Sysfs attributes
echo "FPTU IC Design" > /dev/lab2
cat /dev/lab2
cat /sys/class/lab2_class/lab2/status
cat /sys/class/lab2_class/lab2/buffer_size

# 2. Test buffer reset command
echo "clear" > /dev/lab2
cat /sys/class/lab2_class/lab2/status    # Outputs: EMPTY

# 3. Execute automated test validation scripts
sh /test_driver.sh
sh /test_procfs.sh
```

#### Step 4: Verify NAND Flash (MTD) & Mount JFFS2
```bash
# 1. Load NAND simulator module
modprobe nandsim first_id_byte=0x20 second_id_byte=0x76

# 2. Mount JFFS2 partition to filesystem
mount -t jffs2 /dev/mtdblock1 /mnt/jffs2

# 3. Test persistence across reboot
touch /mnt/jffs2/test_persist.txt
ls -l /mnt/jffs2
```

---

### 4. Complete Project Deliverables Matrix

| Module Directory | Key File / Artifact | Description & Deliverable Role |
| :--- | :--- | :--- |
| [`driver/`](./lab02_device_driver/driver/) | [`lab2_driver.c`](./lab02_device_driver/driver/lab2_driver.c), [`lab2_driver.ko`](./lab02_device_driver/driver/lab2_driver.ko) | Kernel character driver source code and compiled ARM module |
| [`driver/`](./lab02_device_driver/driver/) | [`Makefile`](./lab02_device_driver/driver/Makefile) | Out-of-tree Linux kernel module compilation configuration |
| [`rootfs/`](./lab02_device_driver/rootfs/) | [`test_driver.sh`](./lab02_device_driver/rootfs/test_driver.sh), [`test_procfs.sh`](./lab02_device_driver/rootfs/test_procfs.sh) | Automated verification shell scripts for device I/O and telemetry |
| [`logs/`](./lab02_device_driver/logs/) | [`boot_log.txt`](./lab02_device_driver/logs/boot_log.txt), [`driver_test.txt`](./lab02_device_driver/logs/driver_test.txt), [`mtd_jffs2.txt`](./lab02_device_driver/logs/mtd_jffs2.txt) | Verified execution logs covering boot sequence, character I/O, and NAND flash |
| [`docs/`](./lab02_device_driver/docs/) | [`architecture_diagram.png`](./lab02_device_driver/docs/architecture_diagram.png) | System architecture diagram detailing user-kernel space data path |
| [`report/`](./lab02_device_driver/report/) | [`lab 2.pdf`](./lab02_device_driver/report/lab%202.pdf) | Formal technical engineering PDF report for Laboratory 02 |

---

## 🔬 Lab 03: Embedded Linux, Root Filesystem & Performance Analysis

### 1. Project Overview

This lab contains an Embedded Linux root filesystem image and a collection of C applications used for debugging, memory analysis, and performance investigation.

### 2. Implementation Artifacts

- **Applications ([`apps/`](./lab03_embedded_linux_rootfs/apps/)):** C source files and corresponding application binaries, including `buggy_app`, `leaky_app`, and `leaky_app_fixed`.
- **Root Filesystem ([`output/`](./lab03_embedded_linux_rootfs/output/)):** Packaged root filesystem image [`initramfs_lab3.cpio.gz`](./lab03_embedded_linux_rootfs/output/initramfs_lab3.cpio.gz).
- **Debugging and Profiling Evidence ([`logs/`](./lab03_embedded_linux_rootfs/logs/)):** GDB session logs, `strace` summaries, Valgrind reports, `perf` statistics and reports, a latency histogram, and a flame graph.
- **Technical Report ([`report/`](./lab03_embedded_linux_rootfs/report/)):** [`SE204290.pdf`](./lab03_embedded_linux_rootfs/report/SE204290.pdf).

### 3. Validation and Analysis Evidence

The repository includes artifacts for examining application behavior and memory usage, reviewing debugger sessions, and analyzing performance measurements. Refer to the saved logs and report for the actual test procedures and recorded results.

---

## 🔬 Assignment 01 – How to Write a Device Driver

**Embedded Linux Systems (LOS201) · FPT University – Ho Chi Minh City Campus · Lecturer: Phạm Thế Vinh**

> `ioctl Interface | Misc Device | Driver Analysis | ARMv7 Target`

### 1. Architectural Overview & ioctl Data Flow
This assignment implements two independent Linux kernel drivers for the ARMv7 `vexpress-a9` target emulated by QEMU (Linux 5.15, Cortex-A9, 512 MB, initramfs). `asgn1_driver` extends the LAB-02 character driver with a four-command `ioctl` interface, an internal buffer, operation counters and two operating modes. `counter_driver` is a standalone misc device that exposes an atomic hardware-style counter through `/dev/counter` and `/proc/counter_info`. Both drivers are exercised from userspace by shell test scripts and a small ioctl test program.

#### System Architecture

<img width="419" height="277" alt="image" src="https://github.com/user-attachments/assets/cc385383-5ff5-4578-84dc-c90381848366" />

### 2. Task-by-Task Implementation Summary & Technical Evaluation

#### 📌 Task 1: ioctl Interface – `asgn1_driver` (40 pts)
- **Driver Source ([`asgn1_driver.c`](./task1_ioctl/asgn1_driver.c), [`asgn1_ioctl.h`](./task1_ioctl/asgn1_ioctl.h)):**
  * Registered with `register_chrdev()` on a hand-chosen major in 241–254; node `/dev/asgn1` is created with `mknod`. Implements `open()`, `read()`, `write()`, `release()` and `unlocked_ioctl`, plus `/proc/asgn1_info`.
  * Three separated layers: **interface** (`file_operations`, ioctl dispatch), **operation** (mode handling, prefixing, statistics) and **data** (buffer, counters, version string).
  * A `mutex` protects every access to the buffer and counters; `copy_to_user()` / `copy_from_user()` are used for all user ↔ kernel transfers (no `memcpy()`).
  * `dmesg` logs every `open()`, `release()`, `write()` and each ioctl command; module unload prints a cleanup message.
- **Shared Header ([`asgn1_ioctl.h`](./task1_ioctl/asgn1_ioctl.h)):** one header used by both the kernel module and the userspace test, defining the magic number, `struct asgn1_stats` and all four commands with `_IO` / `_IOR` / `_IOW`.

| ioctl Command | Direction | Argument | Behavior |
| :--- | :---: | :--- | :--- |
| `ASGN1_RESET_BUFFER` | `_IO` | none | Clears the buffer, resets `write_count` and `read_count` to 0; `cat /dev/asgn1` then returns an empty string |
| `ASGN1_GET_STATS` | `_IOR` | `struct asgn1_stats` | Returns `open_count`, `write_count`, `read_count`, `buffer_len`, `last_write_size` (and `mode`) via `copy_to_user()` |
| `ASGN1_SET_MODE` | `_IOW` | `int` | Mode 0 (Kernel): prepends `[KERNEL]` to written data. Mode 1 (Echo, default): stores data unchanged. Other values return `-EINVAL` |
| `ASGN1_GET_VERSION` | `_IOR` | `char[64]` | Returns the version string, bounded to the 64-byte userspace buffer |

Any command outside these four returns `-ENOTTY`.

- **Functional Test ([`test_asgn1.sh`](./task1_ioctl/test_asgn1.sh), [`asgn1_user.c`](./task1_ioctl/asgn1_user.c)):** runs inside QEMU; loads the module, creates `/dev/asgn1`, writes and reads back in both modes, calls all four ioctl commands, verifies RESET, sends invalid inputs and unloads the module.

| Test Step | Observed Result | Verdict |
| :--- | :--- | :---: |
| `GET_STATS` after 3 writes and 3 reads | `open_count=10, write_count=3, read_count=3, buffer_len=4, last_write_size=4, mode=1` | ✅ PASS |
| `GET_VERSION` | `asgn1_driver v1.0 - SE203437` | ✅ PASS |
| `SET_MODE` back to Echo | Stored data has no `[KERNEL]` prefix | ✅ PASS |
| `RESET_BUFFER` after a 16-byte write | `write_count`, `read_count`, `buffer_len` = 0; `cat` returns an empty string | ✅ PASS (4 checks) |
| Unknown ioctl cmd `0x6b7f` | Driver logs "unknown ioctl cmd 0x6b7f"; returns `ENOTTY` (25) | ✅ PASS |
| `SET_MODE = 5` | Returns `EINVAL` (22) | ✅ PASS |
| `rmmod` and `dmesg` | "unloaded, cleanup done" printed; module no longer listed | ✅ PASS |
| **Final result** | **17 passed, 0 failed** | ✅ ALL PASS |

---

#### 📌 Task 2: Misc Device Driver – `counter_driver` (30 pts)
- **Driver Source ([`counter_driver.c`](./task2_misc/counter_driver.c)):**
  * Registered through a static `struct miscdevice` named `"counter"` with `misc_register()` / `misc_deregister()`; the kernel assigns major 10 (`MISC_MAJOR`), so `/dev/counter` exists right after `insmod`.
  * **`read()`:** returns the current value as a decimal string with a trailing newline, then increments the counter (auto-increment on read). `*ppos` is handled so the second `read()` returns 0 and `cat` terminates.
  * **`write()`:** copies the user string, parses it with `kstrtoint()` and sets the counter. Writing `0` resets it; negative or non-numeric input returns `-EINVAL`.
  * **Thread safety:** the counter is an `atomic_t` accessed with `atomic_read()`, `atomic_set()` and `atomic_inc()`.
  * **`/proc/counter_info`:** labelled lines for the current value, total reads (increments) and total writes (resets/sets).
  * `MODULE_LICENSE`, `MODULE_AUTHOR` (name and student ID) and `MODULE_DESCRIPTION` are set.
- **Functional Test ([`test.sh`](./task2_misc/test.sh)):** loads the module, prints `/proc/counter_info`, reads `/dev/counter` twice, writes `100`, reads it back, writes `0` to reset, prints `/proc/counter_info` again and unloads the module.

| Step | Observed Output | Verdict |
| :--- | :--- | :---: |
| Initial `/proc/counter_info` | Current Counter Value: 0, Total Reads: 0, Total Writes: 0 | ✅ PASS |
| Two reads of `/dev/counter` | `0` then `1` (auto-increment) | ✅ PASS |
| Write `100`, then read | Read returns `100` | ✅ PASS |
| Write `0` (reset) | Current Counter Value: 0 | ✅ PASS |
| Final `/proc/counter_info` | Total Reads: 3, Total Writes: 2 | ✅ PASS (matches 3 reads, 2 writes) |
| Unload module | Test completes without error | ✅ PASS |

---

#### 📌 Task 3: Analysis & Design Report (20 pts)
- **Technical Report ([`Assignment_1.pdf`](./report/Assignment_1.pdf)):** 12-page PDF covering:
  * **System architecture & project structure** with the high-level architecture diagram and driver interface specifications.
  * **Character vs Block vs Network devices:** comparison by VFS interface, data unit, buffering and embedded examples, with three design decisions (I2C temperature sensor → char, eMMC → block, CAN controller → network stack).
  * **`register_chrdev()` vs `misc_register()`:** major/minor handling, node creation, boilerplate, pros/cons and when to use each.
  * **Why `atomic_t`:** a concrete lost-update race on a plain `int` (`counter++` = load/add/store), solved with `atomic_inc()` (`ldrex`/`strex` on ARMv7).
  * **ioctl magic number and encoding:** `_IOC(dir, type, nr, size)` layout and the decoding of `0x6b7f` as `_IO('k', 127)`.
  * **Experimental evidence matrix** cross-referencing every figure and screenshot.

| Field | Bits | Macro | Example: `ASGN1_GET_VERSION = _IOR(ASGN1_MAGIC, 4, char[64])` |
| :--- | :---: | :--- | :--- |
| `dir` | 31–30 | `_IOC_DIR` | read |
| `size` | 29–16 | `_IOC_SIZE` | 64 |
| `type` (magic) | 15–8 | `_IOC_TYPE` | `ASGN1_MAGIC` |
| `nr` | 7–0 | `_IOC_NR` | 4 |

---

#### 📌 Task 4: Theory Questions (10 pts)
| Question | Key Technical Answer |
| :--- | :--- |
| **Q1.** Module reference counting | `try_module_get()` on open (via `.owner = THIS_MODULE`) and `module_put()` on release; shown in the "Used by" column of `lsmod`. `rmmod` on a busy module fails with `-EBUSY`; `rmmod -f` needs `CONFIG_MODULE_FORCE_UNLOAD`, taints the kernel and risks a crash. |
| **Q2.** `copy_to_user()` vs `memcpy()` | User pointers are untrusted: `copy_to_user()` checks the range with `access_ok()` and uses exception-table fixups, returning bytes not copied instead of oopsing. Direct writes rely on the page-fault handler in kernel context, bypass SMAP/PAN protection and can corrupt kernel memory. |
| **Q3.** MTD vs block device | Raw flash is erased in large blocks, wears out and has bad blocks/ECC (NAND), so it needs MTD plus flash-aware layers (UBI/UBIFS, JFFS2). Raw NAND and SPI/parallel NOR need MTD; eMMC and SD cards have an internal FTL and use the block layer. |
| **Q4.** `*ppos` handling in `read()` | VFS passes `&file->f_pos`; `cat` loops until `read()` returns 0. Ignoring `*ppos` returns a positive count forever, so `cat` never sees EOF while the counter keeps incrementing. With the check, the 2nd call returns 0 and a new `open()` starts at `f_pos = 0`. |

---

### 3. Step-by-Step Reproduction Guide (How to Run)

#### Step 1: Build Drivers & Userspace Test
```bash
# 1. Task 1 – ioctl driver (asgn1_driver.ko) and userspace test program
cd task1_ioctl
make clean && make
arm-linux-gnueabihf-gcc -static -o asgn1_user asgn1_user.c

# 2. Task 2 – misc counter driver (counter_driver.ko)
cd ../task2_misc
make clean && make
```

#### Step 2: Load `asgn1_driver` and Run the Task 1 Test (inside QEMU vexpress-a9)
```bash
insmod asgn1_driver.ko
mknod /dev/asgn1 c <MAJOR> 0
./test_asgn1.sh
```

#### Step 3: Load `counter_driver` and Run the Task 2 Test
```bash
sudo insmod counter_driver.ko
ls -l /dev/counter
cat /proc/counter_info
sudo ./test.sh

# Manual checks
cat /dev/counter
echo 100 > /dev/counter
echo 0   > /dev/counter
echo -5  > /dev/counter
```

#### Step 4: Verify Diagnostics
```bash
dmesg | grep asgn1_driver
cat /proc/asgn1_info
cat /proc/counter_info
```

#### Step 5: Unload Drivers & Packaging for LMS Submission
```bash
rmmod asgn1_driver
sudo rmmod counter_driver

# Package workspace into the required .tar.gz archive
tar -czvf SE203740_TranHoKhanhTan_Asgn01.tar.gz assignment01/
```

---

### 4. Complete Project Deliverables Matrix

#### Repository Structure
```text
assignment01/
├── report/
│   ├── .gitkeep
│   └── Assignment_1.pdf
├── task1_ioctl/
│   ├── Makefile
│   ├── asgn1_driver.c
│   ├── asgn1_ioctl.h
│   ├── asgn1_user.c
│   ├── readme.md
│   └── test_asgn1.sh
└── task2_misc/
    ├── .gitkeep
    ├── Makefile
    ├── Module.symvers
    ├── counter_driver.c
    ├── counter_driver.mod
    ├── counter_driver.mod.c
    ├── counter_driver.mod.o
    ├── counter_driver.o
    ├── modules.order
    └── test.sh
```
| Module Directory | Key File / Artifact | Description & Deliverable Role |
| :--- | :--- | :--- |
| [`task1_ioctl/`](./task1_ioctl/) | [`asgn1_driver.c`](./task1_ioctl/asgn1_driver.c), [`asgn1_ioctl.h`](./task1_ioctl/asgn1_ioctl.h) | Task 1 kernel driver source and the shared ioctl header (magic number, struct, commands) |
| [`task1_ioctl/`](./task1_ioctl/) | [`asgn1_user.c`](./task1_ioctl/asgn1_user.c), [`test_asgn1.sh`](./task1_ioctl/test_asgn1.sh) | Userspace ioctl test program and the QEMU test script (17 checks) |
| [`task1_ioctl/`](./task1_ioctl/) | [`Makefile`](./task1_ioctl/Makefile), [`readme.md`](./task1_ioctl/readme.md) | Build rules for the ARMv7 module and Task 1 notes |
| [`task2_misc/`](./task2_misc/) | [`counter_driver.c`](./task2_misc/counter_driver.c), [`Makefile`](./task2_misc/Makefile) | Task 2 misc device driver source and build rules |
| [`task2_misc/`](./task2_misc/) | [`test.sh`](./task2_misc/test.sh) | Test script for `/dev/counter` and `/proc/counter_info` |
| [`task2_misc/`](./task2_misc/) | [`counter_driver.o`](./task2_misc/counter_driver.o), [`counter_driver.mod`](./task2_misc/counter_driver.mod), [`counter_driver.mod.c`](./task2_misc/counter_driver.mod.c), [`counter_driver.mod.o`](./task2_misc/counter_driver.mod.o), [`modules.order`](./task2_misc/modules.order), [`Module.symvers`](./task2_misc/Module.symvers) | Kbuild build artifacts generated by `make` |
| [`report/`](./report/) | [`Assignment_1.pdf`](./report/Assignment_1.pdf) | Formal technical report (12 pages) with architecture, design analysis, test evidence and theory answers |

---

## 🔬 Assignment 02 – Sensor Monitoring System (SMS)

### 1. Architectural Overview & State Machine Flow
The Sensor Monitoring System (SMS) is an end-to-end, multi-threaded real-time embedded Linux monitoring suite. It samples simulated environmental sensor hardware via a dedicated kernel character driver, buffers samples across asynchronous boundaries, processes threshold alerts, and dispatches data across POSIX IPC pipelines.

#### System Architecture & IPC Pipeline
![SMS Architecture Diagram](./assignment02_sensor_monitoring/docs/architecture_diagram.png?v=2)

#### Finite State Machine (FSM) Lifecycle
![SMS State Machine Diagram](./assignment02_sensor_monitoring/docs/state_machine_diagram.png?v=2)

---

### 2. Task-by-Task Implementation Summary & Technical Evaluation

#### 📌 Task 1: Architecture & Multi-Threaded Daemon (30 pts)
- **Kernel Character Driver ([`sms_sensor_driver.c`](./assignment02_sensor_monitoring/driver/sms_sensor_driver.c)):**
  * Registers `/dev/sms_sensor` implementing `open()`, `read()`, `llseek()`, and `release()`. Emits CSV records: `<timestamp_ms>,<temperature>,<humidity>\n`.
  * Enforces rate limiting (`g_min_interval_ms = 100ms`), returning `-EAGAIN` upon rapid calls. Supports runtime reconfiguration via `ioctl(SMS_SET_INTERVAL)` and exports counters to `/proc/sms_stats`.
- **Thread-Safe Ring Buffer ([`circular_buffer.c`](./assignment02_sensor_monitoring/app/circular_buffer.c)):**
  * 64-slot capacity protected by `pthread_mutex_t` and dual condition variables (`not_empty`, `not_full`). Implements non-blocking drop-on-full semantics to protect producer acquisition deadlines.
- **POSIX Multi-Threading Pipeline:**
  * **Sensor Thread ([`sensor_thread.c`](./assignment02_sensor_monitoring/app/sensor_thread.c)):** Samples `/dev/sms_sensor` every 500ms using `clock_nanosleep(CLOCK_MONOTONIC)`.
  * **Processor Thread ([`processor_thread.c`](./assignment02_sensor_monitoring/app/processor_thread.c)):** Computes 10-sample rolling averages, evaluates threshold violations (Temp > 40°C, Humid > 80%, Spike > 5°C), and sends events via `mq_timedsend()`.
  * **Logger & Alert Workers ([`logger_thread.c`](./assignment02_sensor_monitoring/app/logger_thread.c), [`alert_thread.c`](./assignment02_sensor_monitoring/app/alert_thread.c)):** Handles file logging to `/tmp/sms.log` (1MB log rotation, 5s flush) and console alerts to `stderr`.

---

#### 📌 Task 2: Memory Management & Driver Integration Audit (20 pts)
- **Valgrind Memcheck Audit ([`valgrind_sms.txt`](./assignment02_sensor_monitoring/logs/valgrind_sms.txt)):** **0 bytes definitely lost**, 0 bytes indirectly lost, 0 bytes possibly lost, and 0 allocation errors.

| Checkpoint Phase | Timestamp | VmSize | VmRSS (Physical RAM) | VmData (Heap & BSS) | Evaluation Status |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **T1: Initialization** | T = 5s | 104,180 kB | **2,752 kB** | 25,600 kB | 4 worker threads & IPC queues mapped |
| **T2: Steady State** | T = 30s | 104,180 kB | **2,884 kB** | 25,600 kB | I/O page warming (+132 kB physical RAM) |
| **T3: Pre-Exit** | T = 55s | 104,180 kB | **2,888 kB** | 25,600 kB | **Strictly flattened (<0.14% variation, 0 leaks)** |

- **Virtual Memory Segmentation ([`proc_sms_maps.txt`](./assignment02_sensor_monitoring/logs/proc_sms_maps.txt)):** Verified memory layout with Text, Data/BSS, Heap, and discrete ~8MB thread stack segments isolated by guard pages.

---

#### 📌 Task 3: Profiling, Tracing & Interactive GDB Debugging (20 pts)
- **System Call Tracing ([`strace_sms.txt`](./assignment02_sensor_monitoring/logs/strace_sms.txt)):**

| System Call | Time Share (%) | Total Invocations | Purpose / Subsystem Mapping |
| :--- | :---: | :---: | :--- |
| `clock_nanosleep` | **37.79%** | 60 | High-resolution monotonic timer driving periodic Sensor Thread wakeups |
| `mq_timedreceive` | **36.85%** | 120 | Blocking IPC reception in Alert and Logger worker threads |
| `futex` | **17.58%** | 184 | Fast userspace locking for `pthread_mutex_t` and condition variables |
| `read` | **4.82%** | 60 | Reading raw CSV environmental sample frames from `/dev/sms_sensor` |
| `write` | **2.15%** | 64 | Committing formatted logs to `/tmp/sms.log` and alerts to `stderr` |

> **Syscall Verdict:** Over 92% of execution time is spent suspended in kernel wait queues (`clock_nanosleep` + `mq_timedreceive` + `futex`), proving an event-driven, I/O-bound architecture with zero CPU waste on polling.

- **CPU Hotspot Analysis ([`perf_sms.txt`](./assignment02_sensor_monitoring/logs/perf_sms.txt)):** 60.15% overhead concentrated in `entry_SYSCALL_64_after_hwframe` $\rightarrow$ `schedule_hrtimeout_range_clock`.
- **GDB Debug Session ([`11_gdb_debug_session.png`](./assignment02_sensor_monitoring/docs/11_gdb_debug_session.png)):** Breakpoint placed at `processor_thread.c:79`; threshold violation verified via variable fault injection (`set var sample.temperature = 45.0`).

---

#### 📌 Task 4: Real-Time Determinism & ARM Portability (15 pts)
- **Jitter Benchmark ([`jitter_report.txt`](./assignment02_sensor_monitoring/logs/jitter_report.txt)):**

| Metric | SCHED_OTHER (Default CFS) | SCHED_FIFO (RT Priority 50 + mlockall) | Improvement Rate |
| :--- | :---: | :---: | :---: |
| **Minimum Jitter** | 67 μs | **42 μs** | 37.3% reduction |
| **Average Jitter** | 189.68 μs | **112.45 μs** | 40.7% reduction |
| **Maximum Jitter** | 2,601 μs (2.6 ms) | **285 μs (0.28 ms)** | **89.1% reduction (Outliers eliminated)** |
| **P99 Tail Jitter** | 2,601 μs | **240 μs** | **90.7% reduction** |
| **Histogram: 0 – 100 μs** | 13.0% (130 samples) | **68.5% (685 samples)** | Tight clustering around ideal period |
| **Histogram: > 1,000 μs** | 1.0% (10 spikes) | **0.0% (0 spikes)** | Complete elimination of tail latency spikes |

- **ARMv7-A Cross-Compilation:** Built cleanly with `arm-linux-gnueabihf-gcc`. Verified executable: `ELF 32-bit LSB pie executable, ARM, EABI5 version 1 (SYSV)` ([`13_cross_compile_arm.png`](./assignment02_sensor_monitoring/docs/13_cross_compile_arm.png)).

---

#### 📌 Task 5: Technical Report, Synchronization Proof & Deliverables (15 pts)
- **Formal Engineering Report:** Full PDF documentation available at [`report/assignment 2.pdf`](./assignment02_sensor_monitoring/report/assignment%202.pdf).
- **Deadlock Avoidance Proof:** Enforces strict single-lock hierarchical acquisition: no thread ever holds more than one lock simultaneously, rendering circular wait graphs impossible under Coffman's criteria.

---

### 3. Step-by-Step Reproduction Guide (How to Run)

#### Step 1: Build Driver & Applications
```bash
# 1. Compile Kernel Driver (sms_sensor_driver.ko)
cd assignment02_sensor_monitoring/driver
make clean && make

# 2. Compile Userspace Daemon (x86_64 Host and ARMv7 Target)
cd ../app
make clean
make host    # Generates sms_app_x86 for local profiling
make arm     # Generates sms_app for ARMv7 target deployment

# 3. Run Circular Buffer Unit Test Suite
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

### 4. Complete Project Deliverables Matrix

| Module Directory | Key File / Artifact | Description & Deliverable Role |
| :--- | :--- | :--- |
| [`driver/`](./assignment02_sensor_monitoring/driver/) | [`sms_sensor_driver.c`](./assignment02_sensor_monitoring/driver/sms_sensor_driver.c), [`sms_sensor_driver.ko`](./assignment02_sensor_monitoring/driver/sms_sensor_driver.ko) | Kernel character driver source and compiled binary module |
| [`app/`](./assignment02_sensor_monitoring/app/) | [`sms_app.c`](./assignment02_sensor_monitoring/app/sms_app.c), [`sms_app_x86`](./assignment02_sensor_monitoring/app/sms_app_x86), [`sms_app`](./assignment02_sensor_monitoring/app/sms_app) | Multi-threaded daemon source and dual-architecture binaries |
| [`output/`](./assignment02_sensor_monitoring/output/) | [`initramfs_asgn2.cpio.gz`](./assignment02_sensor_monitoring/output/initramfs_asgn2.cpio.gz) | Standalone bootable root filesystem image |
| [`logs/`](./assignment02_sensor_monitoring/logs/) | [`perf_sms.txt`](./assignment02_sensor_monitoring/logs/perf_sms.txt), [`strace_sms.txt`](./assignment02_sensor_monitoring/logs/strace_sms.txt), [`valgrind_sms.txt`](./assignment02_sensor_monitoring/logs/valgrind_sms.txt) | Profiling, tracing, and memory audit verification logs |
| [`logs/`](./assignment02_sensor_monitoring/logs/) | [`proc_sms_stats_before.txt`](./assignment02_sensor_monitoring/logs/proc_sms_stats_before.txt), [`jitter_report.txt`](./assignment02_sensor_monitoring/logs/jitter_report.txt), [`sms.log`](./assignment02_sensor_monitoring/logs/sms.log) | ProcFS snapshots, real-time jitter benchmarks, and daemon log output |
| [`docs/`](./assignment02_sensor_monitoring/docs/) | [`architecture_diagram.png?v=2`](./assignment02_sensor_monitoring/docs/architecture_diagram.png?v=2), [`state_machine_diagram.png?v=2`](./assignment02_sensor_monitoring/docs/state_machine_diagram.png?v=2) | System architecture & finite state machine schematics |
| [`report/`](./assignment02_sensor_monitoring/report/) | [`assignment 2.pdf`](./assignment02_sensor_monitoring/report/assignment%202.pdf) | Formal technical engineering report in PDF format |

---


## 🛠️ Team Collaboration Protocol

1. **Keep `main` Clean:** All direct commits to `main` are restricted. Work is conducted on branches (`feature/<name>` or `docs/<name>`).
2. **Pull Before Work:** Always execute `git pull origin main` prior to modifying any shared markdown documentation or configuration files.
3. **Pull Request Verification:** Submit changes through GitHub Pull Requests with descriptive summaries and verified test outputs.
