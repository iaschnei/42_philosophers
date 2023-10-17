# 42_philosophers
A program in C using multithreading to simulate life of philosophers !\
The goal is to solve the dining philosophers problem : https://en.wikipedia.org/wiki/Dining_philosophers_problem

In short, we have a set number of philosophers who need to eat, sleep for a certain time and think.
They have one fork each and need 2 forks to eat, they have to take their neighbour's fork and their own fork to be able to eat.
If they do not eat before they reach `time-to-die`, they die.
I used C threads and mutexes to be able to solve this problem !
![image](https://github.com/iaschnei/42_philosophers/assets/141677415/87b26d6a-101b-4e21-a2d4-29e1dd39b732)

# Usage:

# Usage:
```console
~ make
~ ./philo [number of philo] [time-to-die] [time-to-eat] [time-to-sleep] (optional)[number-of-meals]
```
