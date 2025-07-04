# Dining Philosophers Problem (Pthreads Implementation)

This project is a solution to the **Dining Philosophers Problem**, implemented using **Pthreads**, **mutex locks**, and **condition variables** in C. It was created as part of a course assignment to understand thread synchronization and avoid issues like deadlock and starvation.

## 🧠 Problem Statement

Five philosophers sit around a table. Each philosopher thinks for a while, then tries to eat. To eat, they need two forks: one on their left and one on their right. Philosophers must:
- Not cause deadlock
- Avoid starvation
- Share forks properly (mutual exclusion)

## 🔧 Features

- 5 threads (one for each philosopher)
- Random thinking and eating time (1–3 seconds)
- Mutex for shared state protection
- Condition variables to signal availability of forks
- Clear output showing philosopher states:
  - THINKING
  - HUNGRY
  - EATING

## 🚀 How to Compile and Run

```bash
gcc dining_philosophers.c -o dining_philosophers -lpthread
./dining_philosophers
