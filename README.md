# Operating Systems Programming Assignment - Spring 2026

This repository contains solutions for the mandatory section and one optional task from the OS Projects assignment.

## Project Structure

```
os_project/
├── taskA_word_counter/      (Mandatory - Word Counter with Pipes)
├── taskB_elusive_cursor/    (Mandatory - Windows Elusive Cursor)
├── taskC_parallel_matrix/   (Mandatory - Parallel Matrix Adder)
├── taskD_mlq_scheduler/    (Mandatory - Multilevel Queue Scheduler)
├── taskE_rt_scheduler/      (Mandatory - Real-Time Scheduler)
├── task6_kernel_module/     (Optional - Linux Kernel Module)
└── README.md
```

---

## Mandatory Section

### A. Word Counter with Pipes (taskA_word_counter)

**Description:** 
Parent process forks multiple children. Each child counts words in a specific file or string and sends the count back to the parent via a pipe. The parent then sums up the results.

**Features:**
- Dynamic file input from user
- Error handling: returns -1 for missing files
- Supports both file names and inline strings
- Each child process communicates via Unix pipes

**How to Compile & Run:**
```bash
cd taskA_word_counter
make clean
make

# Run the program
./word_counter

# Example input:
# file1.txt
# string: hello world test
# done
```

**Expected Output:**
```
=== Word Counter with Pipes ===
Enter file names (one per line), or strings starting with 'string:', or 'done' to finish:
> file1.txt
> string: hello world test
> done

Processing 2 tasks (1 files, 1 strings)...

Child 1 (file 'file1.txt'): 4 words
Child 2 (string 1): 3 words

=== FINAL RESULT ===
Total word count: 7
```

---

### B. The Elusive Cursor (taskB_elusive_cursor)

**Description:**
A Windows Win32 application that makes the mouse cursor "jump" or move away whenever the user tries to click. Uses key Windows APIs as required.

**APIs Used:**
- `SetCursorPos(x, y)` - Forcefully move the mouse
- `GetCursorPos(&point)` - Track current cursor position
- `SetTimer()` - Create the interval for cursor movement
- `GetSystemMetrics()` - Keep cursor within screen boundaries
- `RegisterHotKey()` - Secret way to stop the program

**How to Compile & Run (on Windows with MinGW):**
```bash
cd taskB_elusive_cursor
make

# Run the executable
./elusive_cursor.exe
```

**How it Works:**
- Jitters cursor every 100ms by random offset (±30 pixels)
- Secret hotkey: **Ctrl+Shift+X** to stop the program
- Cursor stays within screen bounds using GetSystemMetrics

**Compilation Note:** Requires Windows SDK and MinGW-w64 or Visual Studio.

---

### C. Parallel Matrix Adder (taskC_parallel_matrix)

**Description:**
Multithreaded Linux program where each thread is assigned a specific set of rows from two matrices. Threads add their assigned rows in parallel and store results in a third matrix.

**Features:**
- User-chosen thread count via command line
- Data partitioning: Each thread handles specific rows
- Independent writes: No two threads write to the same memory
- Read-only inputs: Source matrices never modified
- Timing tests included
- Handles remainder rows (N % thread_count)

**How to Compile & Run:**
```bash
cd taskC_parallel_matrix
make clean
make

# Run with custom parameters: ./parallel_matrix <threads> <rows> <cols>
./parallel_matrix 4 100 100

# Or test different thread counts
./parallel_matrix 1 100 100   # Single thread
./parallel_matrix 8 100 100  # 8 threads
```

**Expected Output:**
```
=== Parallel Matrix Adder ===
Matrix size: 100 x 100
Number of threads: 4
Computation time: 0.17 ms

Sample results (first 3x3):
155 98 64 
29 133 106 
96 70 56 
```

---

### D. Multilevel Queue Scheduler (taskD_mlq_scheduler)

**Description:**
Simulates a time-sliced multilevel queue (MLQ) scheduler with three queues, each using a different algorithm and fixed CPU share.

**Configuration:**
- Queue 1 (System): 50% CPU time, Round Robin (RR)
- Queue 2 (Interactive): 30% CPU time, Shortest Job First (SJF)
- Queue 3 (Batch): 20% CPU time, First-Come First-Served (FCFS)

**Features:**
- Time slicing: 5s for Q1, 3s for Q2, 2s for Q3 per cycle
- Outputs waiting time, turnaround time, response time
- Gantt chart showing execution order

**How to Compile & Run:**
```bash
cd taskD_mlq_scheduler
make clean
make
./mlq_scheduler
```

**Expected Output:**
```
=== Multilevel Queue Scheduler ===

Queue 1 (System, RR): 1 processes
Queue 2 (Interactive, SJF): 2 processes
Queue 3 (Batch, FCFS): 2 processes

=== Scheduling Simulation ===
Time slices: Q1=5s, Q2=3s, Q3=2s
Time 0-2: P1 (Q1-RR)
...

=== Results Table ===
PID   Arrival  Burst    Wait     Turnaround Response  
----------------------------------------------
1     0        10       6        16         0         
...

Average: Wait=15.80, Turnaround=24.00, Response=10.40
```

---

### E. Real-Time Scheduler & Schedulability Analyzer (taskE_rt_scheduler)

**Description:**
Implements both Rate Monotonic (RM) and Earliest Deadline First (EDF) scheduling algorithms with schedulability analysis.

**Features:**
- RM: Static priority based on period (shorter period = higher priority)
- EDF: Dynamic priority based on absolute deadline
- Schedulability testing using utilization bounds:
  - RM Bound: n(2^(1/n) - 1) ≈ 0.69 for large n
  - EDF Bound: U ≤ 1.0 (always feasible if U ≤ 1)
- Deadline miss reporting
- Hyperperiod simulation

**Test Case:**
| Task | Period | Execution | Deadline | Utilization |
|------|--------|-----------|-----------|-------------|
| τ₁   | 5      | 2         | 5         | 0.40        |
| τ₂   | 10     | 4         | 10        | 0.40        |
| τ₃   | 20     | 1         | 20        | 0.05        |
| Total|        |           |           | **0.85**   |

**How to Compile & Run:**
```bash
cd taskE_rt_scheduler
make clean
make
./rt_scheduler
```

**Expected Output:**
```
=== Real-Time Scheduler & Schedulability Analyzer ===

Task Set:
Task  Period  Exec  Deadline
----  ------  ----  --------
1     5       2     5
2     10      4     10
3     20      1     20

=== Schedulability Analysis ===
RM Test: Utilization U=0.85, Bound=0.78
EDF Test: Utilization U=0.85, Bound=1.0

RM is NOT guaranteed feasible
EDF is feasible
...
```

---

## Optional Section

### A. Linux Kernel Module (task6_kernel_module)

**Description:**
A simple Linux kernel module that prints GOLDEN_RATIO_PRIME on load and GCD(3700, 24) on unload.

**Features:**
- `module_init()`: Prints GOLDEN_RATIO_PRIME using kernel's hash.h
- `module_exit()`: Computes and prints GCD(3700, 24) using kernel's gcd.h
- Uses kernel printk() instead of printf()

**How to Compile & Run (on Linux with kernel headers):**
```bash
cd task6_kernel_module
make clean
make

# Load the module
sudo insmod golden_prime.ko

# Check kernel log
dmesg

# Unload the module
sudo rmmod golden_prime

# Verify it's unloaded
lsmod | grep golden_prime
```

**Expected Output (from dmesg):**
```
[12345.678901] Loading Kernel Module
[12345.678902] GOLDEN_RATIO_PRIME = 2724001951
[12345.789012] Removing Kernel Module
[12345.789013] GCD(3700, 24) = 4
```

---

## Summary of APIs/Concepts Used

| Task | Key APIs/Concepts |
|------|------------------|
| A | pipe(), fork(), write(), read(), wait() |
| B | SetCursorPos, GetCursorPos, SetTimer, GetSystemMetrics, RegisterHotKey |
| C | pthread_create(), pthread_join(), pthread_mutex (not needed - independent writes) |
| D | FCFS, SJF, Round Robin, time slicing, priority queues |
| E | Rate Monotonic, EDF, utilization bounds, deadlines |
| 6 | module_init(), module_exit(), printk(), kernel space vs user space |

---

## Compilation Commands Summary

```bash
# Task A
cd taskA_word_counter && make

# Task C
cd taskC_parallel_matrix && make

# Task D
cd taskD_mlq_scheduler && make

# Task E
cd taskE_rt_scheduler && make

# Task 6 (requires Linux kernel headers)
cd task6_kernel_module && make
```

---

*For Task B (Windows), compile on Windows with MinGW or Visual Studio.*
