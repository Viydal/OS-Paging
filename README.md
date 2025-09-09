# Assignment 2 Sem 2 2025 OS: Paging

## Overview

This project implements a simulator for a virtual memory system with a single-level page table.
The simulator reads a memory trace and simulates how pages are loaded into memory, replaced, and written back to disk depending on the chosen page replacement algorithm.

The simulator supports:

1. Fixed page/frame size: 4 KB (4096 bytes)

2. Page replacement algorithms:

  * rand → random replacement

  * lru → least recently used

  * esc → clock/second-chance (from textbook section 22.8)

---

## 📂 Project Structure

```
repo/
├── memsim.c         # main source file
├── traces/          # sample trace files
├── README.md        # documentation
└── Makefile         # (optional) build instructions
```

---

## ⚙️ Requirements

* Compiler (e.g., `gcc`)
* Standard C libraries

---

## 🛠️ Build

```bash
gcc -o memsim memsim.c
```

---

## 🚀 Usage

```bash
./memsim <trace_file> <num_frames> <replacement_algorithm> <mode>
```

### Arguments (to be changed)

* `<trace_file>`: input memory trace file
* `<num_frames>`: number of page frames in memory
* `<replacement_algorithm>`: `rand` | `fifo` | `lru` | `clock`
* `<mode>`: `quiet` | `debug`

---

## 🧪 Example

```bash
./memsim traces/trace1 4 lru debug
```

---

## 📊 Output

* Total memory frames
* Events in trace
* Total disk reads
* Total disk writes
* Page fault rate

---

## ✨ Contributors

* Michelle Nguyen
* Riley Turner
* Rory Long
