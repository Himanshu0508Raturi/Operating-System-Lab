# Operating Systems Lab – 5th Semester 👨‍💻

A comprehensive collection of practical programs and implementations for core **Operating Systems** concepts, completed during the 5th semester.  This repository serves as a hands-on guide to understanding OS fundamentals through code implementations.

---

## 📖 About

This repository contains implementations of fundamental operating system algorithms and concepts including:

- **Process Management**: Process creation, forking, and lifecycle management
- **CPU Scheduling Algorithms**:  FCFS, SJF (Preemptive & Non-Preemptive), LJF (Preemptive & Non-Preemptive), Round Robin
- **Inter-Process Communication (IPC)**: Shared memory, pipes, and message queues
- **Synchronization**: Semaphores, mutexes, and classic problems (Dining Philosophers)
- **Disk Scheduling**: SCAN, C-SCAN, and other disk scheduling algorithms
- **Memory Management**: Page replacement algorithms and memory allocation strategies

Each program includes practical implementations with detailed comments, making it easy to understand the underlying concepts and logic.

---

## 🗂️ Repository Structure

```
Operating-System-Lab/
├── WEEK1/          # Process creation, forking, exec family
├── WEEK2/          # Process control and system calls
├── WEEK3/          # CPU Scheduling (FCFS, SJF, LJF)
├── WEEK4/          # Round Robin scheduling
├── WEEK5/          # Priority scheduling
├── WEEK6/          # IPC - Shared memory, Pipes, Dining Philosophers
├── WEEK7-10/       # Additional scheduling and synchronization
├── WEEK11-12/      # Disk scheduling algorithms
├── Manual/         # Reference materials and lab manual
└── README.md       # This file
```

---

## 🚀 How to Run

### Prerequisites
- GCC compiler (Linux/WSL recommended)
- Basic understanding of C programming
- Unix/Linux terminal

### Compilation & Execution

#### For C Programs
```bash
gcc filename.c -o output
./output
```

#### For Programs with Threading
```bash
gcc filename.c -o output -lpthread
./output
```

#### For Programs with Semaphores
```bash
gcc filename.c -o output -pthread
./output
```

### On Windows
```powershell
gcc filename.c -o output.exe
.\output.exe
```

> **Tip**: Use WSL (Windows Subsystem for Linux) for better compatibility with Unix system calls. 

---

## 📚 Concepts Covered

### 1. **Process Management**
- Process creation using `fork()`
- Process control with `wait()`, `exec()` family
- Parent-child process relationships
- Process states and transitions

### 2. **CPU Scheduling Algorithms**
- **FCFS (First Come First Serve)** - Non-preemptive
- **SJF (Shortest Job First)** - Preemptive & Non-Preemptive
- **LJF (Longest Job First)** - Preemptive & Non-Preemptive
- **Round Robin** - Time quantum based scheduling
- **Priority Scheduling** - With aging

Performance metrics calculated:
- Average Waiting Time (AWT)
- Average Turnaround Time (ATAT)
- CPU Utilization
- Throughput
- Response Time

### 3. **Inter-Process Communication (IPC)**
- Shared Memory (`shmget`, `shmat`, `shmdt`)
- Pipes (Named and Unnamed)
- Message Queues
- Signals

### 4. **Synchronization**
- Semaphores (`sem_init`, `sem_wait`, `sem_post`)
- Mutex locks
- **Classic Problems**:
  - Dining Philosophers Problem
  - Producer-Consumer Problem
  - Reader-Writer Problem

### 5. **Disk Scheduling**
- SCAN (Elevator Algorithm)
- C-SCAN (Circular SCAN)
- FCFS Disk Scheduling
- SSTF (Shortest Seek Time First)

### 6. **Memory Management**
- Page replacement algorithms
- Memory allocation strategies
- Virtual memory concepts

---

## 🛠️ Tools & Technologies

- **Language**: C
- **Compiler**:  GCC
- **Platform**: Linux/Unix (Ubuntu, Fedora, etc.)
- **Libraries**: 
  - `pthread. h` - POSIX threads
  - `semaphore.h` - Semaphore operations
  - `sys/ipc.h`, `sys/shm.h` - IPC mechanisms
  - `unistd.h` - Unix standard library

---

## 📊 Sample Programs

### Process Creation (WEEK1/3. c)
Demonstrates parent-child process creation with `fork()` and `exec()` family.

### FCFS Scheduling (WEEK3/fcfs.c)
Non-preemptive scheduling algorithm with Gantt chart visualization.

### Dining Philosophers (WEEK6/3.c)
Classical synchronization problem using semaphores to prevent deadlock.

### SCAN Disk Scheduling (WEEK11-12/2.c)
Elevator algorithm for disk head movement optimization.

---

## 🧪 Testing & Debugging

### Memory Leak Detection (Linux)
```bash
valgrind --leak-check=full ./output
```

### Compile with Warnings
```bash
gcc -Wall -Wextra filename.c -o output
```

### Debug Mode
```bash
gcc -g filename.c -o output
gdb ./output
```

---

## 📝 Notes

- All programs are tested on **Linux (Ubuntu 20.04+)** environment
- Some system calls may not work directly on Windows (use WSL)
- Thread-based programs require `-lpthread` flag during compilation
- Input validation is included in most programs

---

## 🎯 Learning Outcomes

After working through this repository, you will: 
- ✅ Understand process lifecycle and management
- ✅ Implement and analyze CPU scheduling algorithms
- ✅ Master IPC mechanisms and synchronization
- ✅ Solve classical OS problems (Dining Philosophers, etc.)
- ✅ Optimize disk scheduling strategies
- ✅ Debug concurrent programs effectively

---

## 🤝 Contributing

Contributions are welcome! If you find bugs or want to add improvements: 
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit changes (`git commit -m 'Add improvement'`)
4. Push to branch (`git push origin feature/improvement`)
5. Open a Pull Request

---

## 📄 License

This project is open-source and available for educational purposes.

---

## 👨‍💻 Author

**Himanshu Raturi**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Profile-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/himanshu-raturi/)
[![GitHub](https://img.shields.io/badge/GitHub-Follow-black?style=for-the-badge&logo=github)](https://github.com/Himanshu0508Raturi)

---

## 📧 Contact

For questions or discussions: 
- LinkedIn: [Himanshu Raturi](https://www.linkedin.com/in/himanshu-raturi/)
- GitHub: [@Himanshu0508Raturi](https://github.com/Himanshu0508Raturi)

---

⭐ **Star this repository if you find it helpful!**