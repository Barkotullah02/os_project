# Operating Systems Programming Assignment - Spring 2026
# Complete Guide for Beginners (No Programming Background Required)

================================================================================
TABLE OF CONTENTS
================================================================================

1. INTRODUCTION - What is this assignment about?
2. PREREQUISITES - What do you need before starting?
3. PROJECT OVERVIEW - All 6 projects explained simply
4. STEP-BY-STEP INSTRUCTIONS - How to compile and run each project
5. TECHNICAL EXPLANATIONS - Concepts explained in plain English
6. TROUBLESHOOTING - Common problems and solutions
7. WHAT TO SUBMIT - Final deliverables

================================================================================
1. INTRODUCTION - WHAT IS THIS ASSIGNMENT ABOUT?
================================================================================

This assignment is for a university course called "Design of Operating System"
(CSC413/CSE315). In this course, you learn how operating systems like Windows,
Linux, and MacOS work under the hood.

For this programming assignment, you need to create 5 small programs (plus 1
optional task) that demonstrate different operating system concepts:

1. How processes communicate (like kids passing notes in class)
2. How Windows handles mouse/keyboard events
3. How multiple CPU cores work together on a task
4. How a computer decides which program to run next
5. How real-time systems (like airplane computers) handle deadlines
6. (Optional) How to add new code to the Linux operating system itself

Don't worry if this sounds complicated! I'll explain everything step by step.

================================================================================
2. PREREQUISITES - WHAT DO YOU NEED?
================================================================================

Before starting, you need:

FOR ALL PROJECTS (Mandatory):
- A computer with macOS, Linux, or Windows
- A terminal application (Command Prompt on Windows, Terminal on Mac/Linux)
- Basic knowledge of how to navigate folders

FOR SPECIFIC PROJECTS:

Task A (Word Counter): Any computer with GCC compiler
  - macOS: Already installed
  - Linux: Already installed  
  - Windows: Install MinGW or use WSL (Windows Subsystem for Linux)

Task B (Windows Cursor): A Windows computer with Visual Studio or MinGW

Task C (Parallel Matrix): Linux or macOS with pthread library
  - Linux: Already installed
  - macOS: Already installed
  - Windows: Use WSL or use a Linux virtual machine

Task D (Scheduler): Any computer with GCC
  - Same as Task A

Task E (Real-Time Scheduler): Any computer with GCC and math library
  - Same as Task A

Task 6 (Kernel Module - Optional): A Linux computer with kernel headers
  - Only works on real Linux (not virtual machine ideally)
  - Requires sudo/root access

================================================================================
3. PROJECT OVERVIEW - ALL 6 PROJECTS EXPLAINED SIMPLY
================================================================================

------------------------------------------------------------------------------
PROJECT A: WORD COUNTER WITH PIPES
------------------------------------------------------------------------------

WHAT IT DOES:
Imagine you have a teacher (parent process) who asks multiple students (child 
processes) to count words in different pages of a book. Each student counts the words
in their assigned page, then passes the count back to the teacher through a "pipe"
(like passing a note). The teacher then adds up all the numbers.

This demonstrates:
- How one program can spawn multiple sub-programs (fork)
- How programs communicate through pipes (like passing notes)
- How to handle errors (like when a student can't find their page)

WHY IT MATTERS:
This is how many real programs work! For example, when you run a command in
Linux that shows you all files, it might spawn one sub-process per CPU core,
each processing different files, then combine the results.

ENHANCEMENTS (What makes it special):
- Can process files OR strings you type in
- Tells you if a file is missing (error code -1)
- Works with any number of files

------------------------------------------------------------------------------
PROJECT B: THE ELUSIVE CURSOR (WINDOWS ONLY)
------------------------------------------------------------------------------

WHAT IT DOES:
You've probably seen those annoying "prank" programs that move your mouse 
cursor away when you try to click something. That's exactly what this program
does! It randomly "jitters" the cursor every 100 milliseconds (that's 10 times
per second!).

This demonstrates:
- How Windows handles mouse/keyboard events
- How to register "hotkeys" (special key combinations)
- How timers work in Windows

WHY IT MATTERS:
Understanding how to control the cursor is fundamental to Windows programming.
The same concepts are used in:
- Custom mouse pointers
- Video game controls
- Accessibility tools (like following cursor for visually impaired)

WINDOWS APIS USED (fancy Windows functions):
- SetCursorPos: Moves cursor to specific screen position
- GetCursorPos: Finds where cursor currently is
- SetTimer: Creates a recurring timer event
- GetSystemMetrics: Gets screen size (so cursor doesn't leave screen)
- RegisterHotKey: Registers a key combination to stop the program

HOW TO STOP IT:
Press CTRL+SHIFT+X all at the same time!

------------------------------------------------------------------------------
PROJECT C: PARALLEL MATRIX ADDER
------------------------------------------------------------------------------

WHAT IT DOES:
Imagine you have two huge tables of numbers (matrices) and you want to add them
together. Instead of doing it one row at a time, you split the work between
multiple "workers" (threads), each worker adding their specific rows.

This demonstrates:
- Multithreading - doing multiple things at once
- How modern CPUs have multiple cores
- How to divide big tasks into smaller pieces

WHY IT MATTERS:
This is how most modern software works! When you:
- Edit a photo in Photoshop - multiple threads for filters, layers, etc.
- Play a video game - one thread for physics, one for graphics, one for AI
- Download a file - splitting data into chunks for faster download

ENHANCEMENTS:
- You choose how many threads (workers)!
- Handles "remainder" rows - if rows don't divide evenly, last worker gets extras
- Includes timing - shows how fast it runs

------------------------------------------------------------------------------
PROJECT D: MULTILEVEL QUEUE SCHEDULER
------------------------------------------------------------------------------

WHAT IT DOES:
Think of a bank with multiple lines (queues):
- Priority line (Queue 1): VIP customers - 50% of teller time
- Regular line (Queue 2): Wait by shortest transaction - 30% of teller time  
- Express line (Queue 3): Quick transactions only - 20% of teller time

The teller (CPU) cycles through each line, giving each queue their allotted time.
This is exactly how your computer decides which program to run!

This demonstrates:
- Priority scheduling (who gets CPU first)
- Different scheduling algorithms (FCFS, SJF, RR)
- Time slicing (giving each queue a time limit)

WHY IT MATTERS:
Every operating system uses scheduling! When you have:
- Multiple browser tabs open
- Music playing while you write a document
- Downloads running in background

Your computer is juggling all these programs using similar scheduling!

QUEUE CONFIGURATION:
- Queue 1 (System): Uses Round Robin (takes turns)
- Queue 2 (Interactive): Uses Shortest Job First (quick jobs first)
- Queue 3 (Batch): Uses First-Come First-Served (who waited longest)

OUTPUT METRICS:
- Waiting Time: How long job waited in queue
- Turnaround Time: Total time from arrival to completion
- Response Time: How long before first time getting CPU

------------------------------------------------------------------------------
PROJECT E: REAL-TIME SCHEDULER & SCHEDULABILITY ANALYZER
------------------------------------------------------------------------------

WHAT IT DOES:
Real-time systems are special computers that MUST respond within deadlines. Think of:
- Airplane control systems - MUST respond within milliseconds or crash
- Medical devices - pacemakers MUST fire at exact intervals
- Factory robots - MUST complete actions in sequence

This program tests if a set of tasks CAN be scheduled (meet all deadlines).
It implements two major algorithms:

1. RATE MONOTONIC (RM):
   - Tasks with SHORTER periods get HIGHER priority
   - Priority never changes (static)
   - Simple but not always optimal

2. EARLIEST DEADLINE FIRST (EDF):
   - Task closest to deadline runs first
   - Priority changes every moment (dynamic)
   - Better utilization but more complex

WHY IT MATTERS:
Real-time systems are EVERYWHERE:
- Car engine control (must inject fuel at exact moments)
- Air traffic control
- Stock trading systems
- Video frame rendering

SCHEDULABILITY TEST:
For RM: Total utilization must be <= n(2^(1/n) - 1)
  For 3 tasks: <= 0.779 (77.9%)
For EDF: Total utilization must be <= 1.0 (100%)

TEST CASE:
Task τ1: Period=5, Execution=2 → Utilization=0.40
Task τ2: Period=10, Execution=4 → Utilization=0.40  
Task τ3: Period=20, Execution=1 → Utilization=0.05
Total = 0.85 (85%)

RM Result: 0.85 > 0.779 → NOT guaranteed feasible
EDF Result: 0.85 <= 1.0 → Guaranteed feasible

------------------------------------------------------------------------------
PROJECT 6 (OPTIONAL): LINUX KERNEL MODULE
------------------------------------------------------------------------------

WHAT IT DOES:
A "kernel module" is code that runs INSIDE the Linux operating system, not as
a regular program. It's like adding a new built-in feature to the OS!

This module:
- When loaded: Prints a special number (GOLDEN_RATIO_PRIME)
- When unloaded: Computes GCD(3700, 24) = 4

This demonstrates:
- Kernel space vs user space
- How Linux can be extended
- Dynamic loading/unloading of code

WHY IT MATTERS:
Kernel modules are how:
- device drivers work (graphics cards, WiFi, etc.)
- Filesystem support is added
- New features are added without recompiling the entire OS

IMPORTANT WARNINGS:
- Bugs in kernel modules can CRASH the entire computer!
- Must have root/sudo access to load/unload
- Always test in virtual machine first!

================================================================================
4. STEP-BY-STEP INSTRUCTIONS
================================================================================

------------------------------------------------------------------------------
TASK A: WORD COUNTER
------------------------------------------------------------------------------

STEP 1: Open Terminal
- macOS: Applications → Utilities → Terminal
- Linux: Press Ctrl+Alt+T or search "Terminal"
- Windows: Press Win+R, type "cmd", press Enter

STEP 2: Navigate to project folder
Type this command (including the quotes if there's a space):
  cd ~/Documents/os_project/taskA_word_counter
  
Or use full path:
  cd /Users/YOUR_USERNAME/Documents/os_project/taskA_word_counter

STEP 3: Compile the program
Type:
  make
  
You should see output like:
  gcc -Wall -Wextra -pedantic -std=c99 -o word_counter word_counter.c
  
If you see any errors, see TROUBLESHOOTING section.

STEP 4: Run the program
Type:
  ./word_counter

STEP 5: Test it
The program will ask for file names. Try these inputs:

Test 1 - Valid file:
  test.txt
  done

(First create a file called "test.txt" with some text in it)

Test 2 - Missing file:
  nonexistent.txt
  done

Expected output: "ERROR - File not found"

Test 3 - String input:
  string: hello world this is fun
  done

Expected output: Shows word count for each input, then total

STEP 6: Understanding output
Look for:
- "Child X (file 'filename'): Y words" - word count per file
- "ERROR - File not found" - file doesn't exist (error code -1)
- "Total word count: Z" - final sum

------------------------------------------------------------------------------
TASK B: ELUSIVE CURSOR (WINDOWS ONLY)
------------------------------------------------------------------------------

STEP 1: Install Windows development tools
Option A: Install Visual Studio Community (free)
  - Download from visualstudio.microsoft.com
  - Install with "Desktop development with C++"

Option B: Install MinGW (lighter)
  - Download from mingw-w64.org
  - Add to PATH

STEP 2: Navigate to project
  cd path/to/taskB_elusive_cursor

STEP 3: Compile
  make

STEP 4: Run
  ./elusive_cursor.exe

STEP 5: Watch the cursor move!
The cursor will randomly jump around screen.

STEP 6: Stop the program
Press CTRL+SHIFT+X simultaneously

------------------------------------------------------------------------------
TASK C: PARALLEL MATRIX ADDER
------------------------------------------------------------------------------

STEP 1: Navigate to project
  cd ~/Documents/os_project/taskC_parallel_matrix

STEP 2: Compile
  make

STEP 3: Run with basic settings (4 threads, 100x100 matrix)
  ./parallel_matrix

STEP 4: Run with custom settings
Usage: ./parallel_matrix [threads] [rows] [cols]

Examples:
  ./parallel_matrix 1 100 100    # Single thread, 100x100 matrix
  ./parallel_matrix 4 100 100    # 4 threads, 100x100 matrix
  ./parallel_matrix 8 200 200    # 8 threads, 200x200 matrix

STEP 5: Understand output
- "Matrix size: X x Y" - dimensions of matrices
- "Number of threads: Z" - how many parallel workers
- "Computation time: X.XX ms" - how long it took
- Sample results - first 3x3 of result matrix

STEP 6: Compare performance
Try running with different thread counts and compare times:
  time ./parallel_matrix 1 500 500
  time ./parallel_matrix 2 500 500
  time ./parallel_matrix 4 500 500
  time ./parallel_matrix 8 500 500

------------------------------------------------------------------------------
TASK D: MULTILEVEL QUEUE SCHEDULER
------------------------------------------------------------------------------

STEP 1: Navigate to project
  cd ~/Documents/os_project/taskD_mlq_scheduler

STEP 2: Compile
  make

STEP 3: Run
  ./mlq_scheduler

STEP 4: Understand output

First section shows queues:
  Queue 1 (System, RR): X processes    - High priority, Round Robin
  Queue 2 (Interactive, SJF): Y processes - Medium priority, Shortest Job First
  Queue 3 (Batch, FCFS): Z processes  - Low priority, First Come First Served

Second section shows Gantt chart:
  Time 0-2: P1 (Q1-RR)
  Time 2-4: P2 (Q2-SJF)
  ...

This shows execution order, which process ran when, and which queue it came from.

Third section is results table:
  PID     - Process ID number
  Arrival - When process started waiting
  Burst   - How much CPU time needed
  Wait    - How long waited in queue (NOT getting CPU)
  Turnaround - Total time from arrival to completion
  Response - Time from arrival to FIRST time getting CPU

------------------------------------------------------------------------------
TASK E: REAL-TIME SCHEDULER
------------------------------------------------------------------------------

STEP 1: Navigate to project
  cd ~/Documents/os_project/taskE_rt_scheduler

STEP 2: Compile
  make

STEP 3: Run
  ./rt_scheduler

STEP 4: Understand output

First section - Task definitions:
  Task  Period  Exec  Deadline
  1     5       2     5
  2     10      4     10
  3     20      1     20

This shows each periodic task's properties.

Second section - Schedulability analysis:
  RM Test: Utilization U=0.85, Bound=0.78
  EDF Test: Utilization U=0.85, Bound=1.0

  RM is NOT guaranteed feasible  ← Because 0.85 > 0.78
  EDF is feasible                  ← Because 0.85 < 1.0

This tells you if the tasks CAN meet their deadlines!

Third section - Simulations:
  RM Simulation runs through time showing which task executes when
  EDF Simulation same but with different algorithm

Fourth section - Summary:
  Shows final verdict on feasibility

------------------------------------------------------------------------------
PROJECT 6 (OPTIONAL): LINUX KERNEL MODULE
------------------------------------------------------------------------------

STEP 1: Requirements
- A Linux computer (real Linux recommended, not virtual machine)
- Root/sudo access
- Linux kernel headers installed

Install on Ubuntu/Debian:
  sudo apt-get install build-essential linux-headers-$(uname -r)

STEP 2: Navigate to project
  cd ~/Documents/os_project/task6_kernel_module

STEP 3: Compile
  make

You should see files being created:
  - golden_prime.ko (the compiled module)
  - various .o and .tmp files

STEP 4: Load the module
  sudo insmod golden_prime.ko

STEP 5: Check if loaded
  lsmod | grep golden_prime

You should see "golden_prime" in the list.

STEP 6: Check kernel log for output
  dmesg | tail -20

You should see lines like:
  [12345.678901] Loading Kernel Module
  [12345.678902] GOLDEN_RATIO_PRIME = 2724001951

The number 2724001951 is GOLDEN_RATIO_PRIME - a special mathematical constant!

STEP 7: Unload the module
  sudo rmmod golden_prime

STEP 8: Check kernel log again
  dmesg | tail -10

You should see:
  [12345.789012] Removing Kernel Module
  [12345.789013] GCD(3700, 24) = 4

GCD = Greatest Common Divisor. The largest number that divides both 3700 and 24 is 4!

WHAT YOU LEARNED:
- The kernel is the core of Linux - it runs in "kernel space"
- Regular programs run in "user space"
- printk() is like printf() but for kernel log
- Kernel modules extend Linux without rebooting!

================================================================================
5. TECHNICAL EXPLANATIONS - CONCEPTS IN PLAIN ENGLISH
================================================================================

------------------------------------------------------------------------------
WHAT IS A PROCESS?
------------------------------------------------------------------------------

Think of a process like a person doing a job. A person (process) can:
- Start a new job (fork)
- Communicate with others (pipes)
- Wait for others to finish (wait)
- Do work (execute)

When you run a program, it becomes a process!

------------------------------------------------------------------------------
WHAT IS A THREAD?
------------------------------------------------------------------------------

A thread is like a worker within a process. A process can have multiple threads,
like one person (process) with multiple hands (threads) doing different things
at the same time!

In a single-core CPU: threads take turns (like one hand at a time)
In a multi-core CPU: threads work truly in parallel (both hands at once!)

------------------------------------------------------------------------------
WHAT IS A PIPE?
------------------------------------------------------------------------------

A pipe is like a tube connecting two processes. One process writes data in
one end, another process reads it from the other end. FIFO = First In,
First Out - like a garden hose!

In UNIX: pipe() creates a pipe, write() puts data in, read() takes data out

------------------------------------------------------------------------------
WHAT IS INTER-PROCESS COMMUNICATION (IPC)?
------------------------------------------------------------------------------

Processes can't normally read each other's memory (for security). When they
need to share data, they must use IPC mechanisms like:
- Pipes (simple, one-way communication)
- Shared memory (both can access same memory)
- Messages (formatted data packets)
- Sockets (like network communication)

------------------------------------------------------------------------------
WHAT IS A SCHEDULER?
------------------------------------------------------------------------------

The scheduler is the "traffic cop" of the operating system. When multiple
programs want to run, the scheduler decides:
- Which program runs first?
- How long does it run?
- What happens when a new program starts?

Different scheduling algorithms optimize for different things:
- Fairness: Everyone gets a turn
- Speed: Minimize total completion time
- Responsiveness: Interactive programs feel snappy
- Real-time: Deadlines MUST be met

------------------------------------------------------------------------------
WHAT IS RATE MONOTONIC (RM)?
------------------------------------------------------------------------------

Simple rule: The task with the SHORTEST PERIOD gets the HIGHEST PRIORITY.

Why? Short period tasks need to run more frequently, so they might miss
deadlines if they wait too long. By giving them high priority, they always
go first.

Pros: Simple, predictable
Cons: Not always optimal, can waste CPU time

------------------------------------------------------------------------------
WHAT IS EDF (EARLIEST DEADLINE FIRST)?
------------------------------------------------------------------------------

Dynamic rule: whichever task has the earliest deadline gets to run now.

Why? The task closest to its deadline is most at risk of missing it!

Pros: Better CPU utilization (up to 100%)
Cons: More complex to implement, harder to analyze

------------------------------------------------------------------------------
WHAT IS KERNEL SPACE VS USER SPACE?
------------------------------------------------------------------------------

Modern operating systems separate programs into two zones:

USER SPACE (where regular programs run):
- Limited permissions
- Can't directly access hardware
- Crashes don't affect other programs much
- Can be paused/killed by OS

KERNEL SPACE (where OS core runs):
- Full permissions to everything
- Direct hardware access
- Crashes can crash the WHOLE system
- Never gets preempted

The line between them is the "privilege ring":
- Ring 0: Kernel (full access)
- Ring 1-2: Device drivers
- Ring 3: User programs (limited access)

================================================================================
6. TROUBLESHOOTING - COMMON PROBLEMS AND SOLUTIONS
================================================================================

------------------------------------------------------------------------------
"command not found" ERROR
------------------------------------------------------------------------------

Problem: When you type "make" or "./word_counter", you get "command not found"

Solution: 
1. Make sure you're in the correct directory
2. Check the executable exists: ls -la *.c shows .c files
3. Check you compiled first: make

------------------------------------------------------------------------------
PERMISSION DENIED ERROR
------------------------------------------------------------------------------

Problem: "./word_counter: Permission denied"

Solution:
  chmod +x word_counter
  
Or recompile:
  make clean
  make

------------------------------------------------------------------------------
"NO SUCH FILE OR DIRECTORY"
------------------------------------------------------------------------------

Problem: Can't find the project folder

Solution:
1. Check your current location: pwd
2. List files in current folder: ls
3. Navigate correctly: cd ~/Documents/os_project/taskA_word_counter

------------------------------------------------------------------------------
"CANNOT FIND -LMP" OR MATH LIBRARY ERROR
------------------------------------------------------------------------------

Problem: Math library not found when compiling

Solution:
For Task E, the Makefile might have double -lm. Edit Makefile:
  Change: CFLAGS = -Wall -Wextra -lm -std=c99
  To: CFLAGS = -Wall -Wextra -std=c99
  And change LDFLAGS = -lm to nothing

------------------------------------------------------------------------------
KERNEL MODULE WON'T COMPILE
------------------------------------------------------------------------------

Problem: "No such file or directory" for kernel headers

Solution:
Install kernel headers:
  sudo apt-get update
  sudo apt-get install build-essential linux-headers-$(uname -r)

------------------------------------------------------------------------------
CAN'T LOAD KERNEL MODULE
------------------------------------------------------------------------------

Problem: "insmod: ERROR: could not insert module"

Solution:
Check dmesg for error:
  dmesg | tail
  
Make sure you're running as root:
  sudo insmod golden_prime.ko

------------------------------------------------------------------------------
WINDOWS TASK B WON'T COMPILE
------------------------------------------------------------------------------

Problem: Various errors

Solution:
1. Make sure you have MinGW or Visual Studio
2. For MinGW, you need Windows SDK installed
3. Try compiling manually:
  gcc -o elusive_cursor.exe elusive_cursor.c -luser32 -lgdi32 -lkernel32

================================================================================
7. WHAT TO SUBMIT - FINAL DELIVERABLES
================================================================================

FILE NAMING FORMAT (IMPORTANT!):
  <Section Number>_<ID>_<Course Name>_<Student Name>.zip
  
Example:
  3_2120117_CSC413-Ezhar_Uddin.zip
  1_2091012_CSE315_Rezwan_Ahmed.zip

CONTENTS OF ZIP FILE:
All your code files in their respective folders:
- taskA_word_counter/ (with .c and Makefile)
- taskB_elusive_cursor/ (with .c and Makefile)  
- taskC_parallel_matrix/ (with .c and Makefile)
- taskD_mlq_scheduler/ (with .c and Makefile)
- taskE_rt_scheduler/ (with .c and Makefile)
- task6_kernel_module/ (optional, with .c and Makefile)

DO NOT INCLUDE:
- Executable binaries (.exe, no extension on Linux)
- Object files (.o)
- Temporary files

SUBMISSION FORMAT:
- All code must be compilable
- Each task in its own folder
- Include Makefile for each task
- Include README or comments explaining

FOR VIVA (PRESENTATION):
Be prepared to explain:
1. How each program works
2. What OS concepts are demonstrated
3. How to compile and run each task
4. For Task B: How each Windows API is used
5. For Task 6 (optional): Kernel space vs user space

================================================================================
END OF README
================================================================================

Good luck with your assignment! Remember:
- Start early
- Test each task separately
- Understand what you're submitting
- Be ready to explain at viva

Questions? Review this README or ask your TA/instructor!