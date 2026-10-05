# FPT University - Linux and Open Source Platform (LOS201)

[![Linux Kernel](https://img.shields.io/badge/Kernel-5.15.0%20LTS-blue.svg?logo=linux&logoColor=white)](https://kernel.org)
[![Target Arch](https://img.shields.io/badge/Architecture-ARMv7--A%20Cortex--A9-orange.svg)](https://developer.arm.com)
[![Platform](https://img.shields.io/badge/Emulator-QEMU%20vexpress--a9-green.svg)](https://www.qemu.org)

This repository contains the coursework, laboratory experiments, and assignments for **Linux and Open Source Platform (LOS201)** at **FPT University - Ho Chi Minh City Campus**.

---

## 👥 Engineering Team

| Full Name | Roll Number | Role | Contribution Area |
| :--- | :---: | :---: | :--- |
| **Hoàng Ngọc Gia Bão** | **SE203238** | **Team Leader** | System Architecture, Character Driver, Integration |
| **Trần Hồ Khánh Tân** | **SE203740** | Member | Driver I/O Verification, Userspace Test Scripts |
| **Nguyễn Trọng Hùng** | **SE204352** | Member | MTD Subsystem, Flash Simulation & Persistence |
| **Nguyễn Quế Vũ** | **SE204290** | Member | Embedded Filesystems Benchmarking & Analysis |
| **Nguyễn Việt Anh** | **SE204364** | Member | Virtual Filesystems (procfs, sysfs), Synchronization |
| **Hồ Phan Anh Tuấn** | **SE203437** | Member | BusyBox Init Orchestration & Exception Handling |

* **Supervising Lecturer:** Mr. Phạm Thế Vinh

---

## 📂 Repository Structure
---

## 🚀 Lab 02 Highlights: Device Driver & File System
* **Character Device Driver:** Registered major `240`, supporting POSIX `open`, `read`, `write`, `release` with `mutex` protection and `copy_to_user` / `copy_from_user` boundary checks.
* **Virtual Diagnostic Interfaces:** Single-open formatted reporting via `/proc/lab2_info` and atomic attributes under `/sys/class/lab2_class/lab2/`.
* **MTD & JFFS2 Filesystem:** Simulated 32MB NAND flash using `nandsim`, verified erase/write routines, and validated persistence across mount/unmount cycles.
* **Automated Boot Orchestration:** Embedded module loading via BusyBox `/etc/init.d/rcS`.
