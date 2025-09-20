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
└── Makefile         # build instructions
```

---

## ⚙️ Requirements

* Compiler (e.g., `gcc`)
* Standard C libraries
* [Optional] Cmake - for debugging and stopping at breakpoints

---

## 🛠️ Build (with normal C++ command lines)

```bash
gcc -o memsim memsim.c
```
or use Makefile
```bash
make run
```

---

## 🚀 Usage

```bash
./memsim <trace_file> <num_frames> <replacement_algorithm> <mode>
```
or use Makefile:
```bash
make gcc
make sixpack
make swim
```
---

## 🛠️ Debugging with CMake
Set up and run the project as a CMake project:
1. When first setting up the project, without a `build` folder: 
```bash
mkdir -p build && cd build && cmake .. && cmake --build . && cd ..
```
2. To rerun, have to delete the build folder first.
```bash
rm -rf build && mkdir -p build && cd build && cmake .. && cmake --build . && cd ..
```
3. The executable `memsim` is created as usual, however, not in the parent directory but in the `build` folder. To use this `memsim`, include the filepath to the `build` folder, for example:
```bash
./build/memsim traces/realTraces/swim.trace 4 lru quiet
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
