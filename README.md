# CPU Scheduler Simulator

A terminal based multicore CPU scheduling simulator in C, modeling process execution, queues, and performance metrics like waiting time, turnaround time, and CPU utilization.

---

## 📝 Overview
Simulates an OS scheduler distributing processes across multiple CPU cores. Tracks process execution step by step and computes system performance metrics.

---

## 🚀 Core Features
- Multicore CPU simulation  
- Ready Queue scheduling  
- Gantt style execution timeline (CLI)  
- Process metrics: CT, TAT, WT  
- CPU metrics: Utilization, Throughput  

---

## 🧠 OS Concepts
- CPU Scheduling & Queues  
- Multi-core execution  
- Turnaround, Waiting, Completion time  
- CPU utilization calculation  

---

## 💻 Language & Concepts
Language: C
Concepts: Operating Systems, CPU Scheduling, Queues, Multi-core Execution, Performance Metrics

---

## ▶️ How to Run CPU Scheduler Simulator
Requirements
- GCC Compiler (MinGW for Windows or gcc for Linux/macOS)
- Terminal / Command Prompt

1. Navigate to your project directory:

```bash
cd path/to/cpu-scheduler-sim
```

2. Compile the program
```bash
gcc main.c -o scheduler
```
This will create an executable file:
scheduler.exe (Windows) or scheduler (Linux/macOS)

3. Run the Program
Windows:
```bash
scheduler.exe
```
Linux/macOS: 
```bash
./scheduler
```

5. Input File Setup
Make sure input.txt is in the same folder as the executable.

6. DONE
If everything is correct, the scheduler will start and display CPU core execution logs in real time.
