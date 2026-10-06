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

* **Supervising Lecturer:** Mr. Phạm Thế Vinh

---

## 📂 Repository Structure

* **`lab01_kernel_boot/`**: Linux Kernel Configuration & System Boot on ARMv7 Architecture.
  * `configs/`: Linux Kernel and BusyBox configuration files (`kernel.config`, `busybox.config`).
  * `rootfs/`: Minimal BusyBox-based initramfs root filesystem used for the ARMv7 Linux boot process.
    * `initramfs/`: Root filesystem containing system initialization scripts, runtime mount points, and BusyBox userspace directories.
      * `etc/`: System initialization configuration including `inittab` and `init.d/rcS`.
      * `dev/`, `proc/`, `sys/`: Device and virtual filesystem mount points used during system startup.
      * `bin/`, `sbin/`, `usr/bin/`, `usr/sbin/`: Userspace executable directories.
  * `output/`: Generated boot artifacts including Linux kernel image (`zImage`), Device Tree Blob (`vexpress-v2p-ca9.dtb`), and compressed initramfs image (`initramfs.cpio.gz`).
  * `report/`: Formal technical PDF laboratory report (`Lab01.pdf`).
* **`lab02_device_driver/`**: Writing Character Device Drivers & Flash Filesystem Management.
  * `driver/`: Kernel module source (`lab2_driver.c`), `Makefile`, and compiled ARM binary (`lab2_driver.ko`).
  * `rootfs/`: BusyBox initialization scripts (`inittab`, `rcS`) and userspace validation suites (`test_driver.sh`, `test_procfs.sh`).
  * `logs/`: Verifiable raw execution terminal logs (`boot_log.txt`, `driver_test.txt`, `procfs_test.txt`, `mtd_jffs2.txt`).
  * `docs/`: Architectural schematics and system design diagrams.
  * `report/`: Formal technical PDF laboratory report (`SE203238_Lab02_BaoCao.pdf`).
* **`lab03_open_source/`**: Open Source Development Workflow & Community Contribution.
* **`assignment01/`**: Advanced Linux Architecture & System Programming.
* **`assignment02/`**: Embedded Linux Capstone Project.
* **`.gitignore`**: High-performance Git filter excluding raw multi-gigabyte kernel build trees and object artifacts.

---
## 🔬 Lab 01: Linux Kernel Configuration & System Boot on ARMv7

### 1. Architectural Overview & System Flow

LAB 01 focuses on configuring, building, and booting an Embedded Linux system for the ARMv7-A Cortex-A9 architecture using QEMU `vexpress-a9`.

The complete boot flow consists of Linux Kernel configuration and cross-compilation, U-Boot bootloader preparation, BusyBox root filesystem construction, initramfs packaging, and final Linux system boot on QEMU.

<img width="341" height="197" alt="image" src="https://github.com/user-attachments/assets/723a2bff-1f18-4bc8-b4ec-36f4b4209d71" />


### 2. Comprehensive Technical Highlights

* **Linux Kernel Configuration & Cross-Compilation:**
  * Configured Linux Kernel `5.15.0 LTS` for the ARMv7-A Cortex-A9 platform.
  * Used the `arm-linux-gnueabihf-` cross-compilation toolchain to build the kernel for ARM.
  * Started from the `vexpress_defconfig` configuration for the QEMU Versatile Express platform.
  * Enabled the required kernel features for initramfs support and the PL011 UART serial console.
  * Generated the ARM kernel image `zImage` and the Device Tree Blob `vexpress-v2p-ca9.dtb`.

* **U-Boot Bootloader:**
  * Configured U-Boot for the `vexpress_ca9x4` platform.
  * Built and executed U-Boot on the QEMU `vexpress-a9` machine.
  * Inspected the U-Boot version, board information, and environment variables.
  * Configured the Linux kernel boot arguments and `bootcmd` using the `bootz` command.

* **BusyBox & Minimal Root Filesystem:**
  * Built BusyBox as a statically linked ARMv7 userspace environment.
  * Created a minimal initramfs root filesystem for the embedded Linux system.
  * Prepared the required directory structure including `/bin`, `/sbin`, `/usr/bin`, `/usr/sbin`, `/dev`, `/proc`, `/sys`, `/tmp`, `/etc`, and `/lib`.
  * Implemented `/init`, `/etc/inittab`, and `/etc/init.d/rcS` for system initialization.
  * Configured the root filesystem to provide a minimal BusyBox-based userspace environment.

* **Linux Boot & Initramfs Integration:**
  * Packaged the BusyBox root filesystem into `initramfs.cpio.gz`.
  * Booted the Linux kernel on QEMU `vexpress-a9` using the kernel image, Device Tree Blob, and initramfs.
  * Configured the kernel command line with the `ttyAMA0` serial console and `/sbin/init`.
  * Verified the transition from the Linux kernel to the BusyBox userspace shell.

* **System Verification:**
  * Verified the running kernel using `uname -a`.
  * Inspected ARM CPU information through `/proc/cpuinfo`.
  * Checked memory information through `/proc/meminfo`.
  * Inspected available device nodes under `/dev`.
  * Verified mounted filesystems using `mount`.
  * Inspected running processes using `ps`.
  * Verified available CPUs through `/sys/devices/system/cpu/possible`.

### 3. Project Structure

The LAB 01 deliverables are organized as follows:

```text
lab01_kernel_boot/
├── configs/
│   ├── kernel.config
│   └── busybox.config  
│
├── output/
│   ├── zImage
│   ├── vexpress-v2p-ca9.dtb
│   └── initramfs.cpio.gz
│
├── report/
│   └── Lab01.pdf
│
└── rootfs/
    └── initramfs/
        ├── bin/
        ├── dev/
        ├── etc/
        │   ├── inittab
        │   └── init.d/
        │       └── rcS
        ├── lib/
        ├── proc/
        ├── sbin/
        ├── sys/
        ├── tmp/
        ├── usr/
        │   ├── bin/
        │   └── sbin/
        └── init   
```

## 🔬 Lab 02: Writing Device Drivers & File System Management

### 1. Architectural Overview & System Flow
The driver bridges userspace system call requests with physical/emulated hardware resources while strictly maintaining kernel space isolation and data integrity.

![Architecture Diagram](lab02_device_driver/docs/architecture_diagram.png)

### 2. Comprehensive Technical Highlights
* **Kernel Character Device Driver Subsystem:**
  * **Major/Minor Allocation:** Dynamically bound to Major number `240` (reserved for local/experimental use) and Minor `0` mapped to device special node `/dev/lab2`.
  * **POSIX File Operations (`fops`):** Implemented handlers for `open`, `release`, `read`, and `write` system calls.
  * **Zero-Panic Memory Safety:** Data transfers between userspace and kernel space are strictly handled via `copy_from_user()` and `copy_to_user()`. This prevents kernel page faults and privilege escalation attacks by verifying user pointer legality via kernel Exception Tables.
  * **Concurrency & Race Condition Prevention:** All critical sections accessing the 1024-byte `device_buffer` and tracking variables (`buffer_len`, `open_count`) are serialized via `DEFINE_MUTEX(lab2_mutex)` to guarantee thread safety in multi-threaded SMP environments.

* **Diagnostic & Export Virtual Filesystems:**
  * **procfs (`/proc/lab2_info`):** Integrated via the `seq_file` interface and `single_open()` helper to provide formatted, multi-line diagnostic summaries (Major ID, buffer capacity, active payload size, cumulative open count, and live buffer contents).
  * **sysfs (`/sys/class/lab2_class/lab2/`):** Decomposed internal driver variables into discrete, atomic, read-only attributes (`buffer_len`, `open_count`, `last_data`) utilizing the `DEVICE_ATTR_RO` macro and unified `kobject` architecture.

* **Memory Technology Device (MTD) & JFFS2 Subsystem:**
  * **Flash Hardware Simulation:** Emulated a 32MB physical NAND flash profile with 512-byte page size and 16KB eraseblock geometry (`0x4000`) using the host `nandsim` module.
  * **Erase/Program Workflows:** Cleaned partitions via `flash_erase`, synthesized structured filesystem images via `mkfs.jffs2 --no-cleanmarkers`, and wrote images using `nandwrite`.
  * **Verified Persistence:** Validated runtime writes, appending data, and verified full data retention across unmount (`umount`) and remount cycles on `/dev/mtdblock1`.
  * **Node Inspection:** Extracted raw flash blocks using `nanddump` and confirmed the native JFFS2 magic bitmask (`0x85 0x19`) via `hexdump`.

* **Automated Boot Orchestration via BusyBox Init:**
  * Configured BusyBox `/sbin/init` through `/etc/inittab` to execute early system initialization via `/etc/init.d/rcS`.
  * Fully automated the detection and dynamic insertion (`insmod`) of `lab2_driver.ko` and automated node creation (`mknod /dev/lab2 c 240 0`) before the interactive root shell spawns.

---

## 🛠️ Team Collaboration Protocol

1. **Keep `main` Clean:** All direct commits to `main` are restricted. Work is conducted on branches (`feature/<name>` or `docs/<name>`).
2. **Pull Before Work:** Always execute `git pull origin main` prior to modifying any shared markdown documentation or configuration files.
3. **Pull Request Verification:** Submit changes through GitHub Pull Requests with descriptive summaries and verified test outputs.
