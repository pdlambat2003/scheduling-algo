# Comprehensive Scheduling Algorithms

Welcome to the Comprehensive Scheduling Algorithms<br>
Here, I've implemented various scheduling algorithms in C++ using object-oriented programming principles. I've also attempted to demonstrate a combined use case of these algorithms through a simple airport terminal scheduling concept. Keep in mind that this is a rough idea and serves as an illustrative example.

## Scheduling Algorithms

### 1. First Come First Serve (FCFS)

- **Brief description:** The FCFS scheduling algorithm is a non-preemptive scheduling algorithm where processes are executed in the order they arrive. The CPU is assigned to the first process in the ready queue, and it continues to execute until it completes or blocks for I/O. Once the first process is finished, the CPU is allocated to the next process in the queue, and so on. FCFS is simple to understand and implement but can lead to poor turnaround times, especially if long processes are scheduled first.

### 2. Shortest Job First (SJF) - Non-preemptive

- **Brief description:** The SJF (Shortest Job First) scheduling algorithm, in its non-preemptive form, schedules the process with the smallest burst time next. When a process arrives, the scheduler compares its burst time with the burst times of all other processes currently in the ready queue. The process with the smallest burst time is selected for execution next. SJF minimizes the average waiting time and turnaround time, assuming that all processes are available at the beginning. However, it can cause starvation for longer processes if shorter ones continually arrive.

### 3. Shortest Job First (SJF) - Preemptive

- **Brief description:** The SJF (Shortest Job First) scheduling algorithm, in its preemptive form, schedules the process with the smallest remaining burst time next. Whenever a new process arrives or a currently running process completes its burst, the scheduler compares the remaining burst times of all processes in the ready queue. The process with the smallest remaining burst time is selected for execution next. SJF preemptive aims to minimize the average waiting time and turnaround time by allowing shorter jobs to be executed first, even if longer jobs have already started. However, it can lead to a high rate of context switches and may not be suitable for all environments.

### 4. Priority Based Scheduling - Non-preemptive

- **Brief description:** In the Priority Based scheduling algorithm, each process is assigned a priority. The scheduler selects the process with the highest priority from the ready queue for execution. In the non-preemptive version, once a process starts executing, it continues until it completes or blocks for I/O. The selection of the next process to run is only made when the currently running process finishes. Priority Based scheduling can be useful for scenarios where certain processes require immediate attention or have higher importance compared to others.

### 5. Priority Based Scheduling - Preemptive

- **Brief description:** Priority Based scheduling in its preemptive form allows the scheduler to preempt a running process if a new process with a higher priority arrives. The scheduler continuously monitors the ready queue for any new processes and compares their priorities with the priority of the currently running process. If a process with a higher priority enters the ready queue, the scheduler suspends the current process and switches to the higher priority process. Preemptive Priority Based scheduling ensures that processes with higher priority are executed promptly, which is critical for time-sensitive tasks or real-time systems.

### 6. Round Robin Scheduling

- **Brief description:** The Round Robin scheduling algorithm is a preemptive scheduling algorithm that allocates a fixed time slice to each process in the ready queue. When a process is scheduled, it is allowed to execute for a predefined time quantum or time slice. If the process completes within this time quantum, it is removed from the CPU. If the process doesn't finish within the time quantum, it is preempted, and the CPU is assigned to the next process in the ready queue. The preempted process is placed back in the ready queue to await its turn again. Round Robin scheduling ensures fairness among processes and prevents starvation, but it may suffer from high context switch overhead if the time quantum is too small.

## Features

- Terminal allocation based on various scheduling algorithms.
- Support for both non-preemptive and preemptive scheduling.
- Efficient management of airplane arrivals and departures.
- User-friendly interface for inputting airplane details and viewing scheduling results.

## Future Improvements

While the current implementation provides basic scheduling functionality, there is room for further enhancements, including:
- Implementing more advanced scheduling algorithms.
- Adding support for dynamic scheduling based on real-time data.
- Enhancing the user interface for better usability.
