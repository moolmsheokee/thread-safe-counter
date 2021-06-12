# PROJECT NO.2 Thread Safety by Semaphore

+ OS environment is WSL2

+ Use 'time' command for executing files 1,000,000 times.
---
## **MUTEX**
![mutex](https://user-images.githubusercontent.com/84587146/121786887-b47a2400-cbfd-11eb-95db-874dbc9984a1.png)
## **SEMAPHORE**
![semaphore](https://user-images.githubusercontent.com/84587146/121786896-c0fe7c80-cbfd-11eb-9f59-711226dbc42b.png)

---
## **MY ANALYSIS**
When Multiple users(threads or processes) use the same resource, it should be used in isolation(mutual exclusion). Like a counter, critical section should be used in isolation. We can protect critical section with 'mutex' and 'semaphore'. In Mutex, only one thread holding the lock enters. It means that mutex can be unlocked by who locked it. Otherwise, semaphore makes multiple threads can enter with a counter and ther is no lock owner concept. So it can be used for other sychronization purpose.
Anyway, mutex is enormously faster than semaphore when I executed two c files.

Then why it might happened?

I think that it might happen with a little differences. When using a Mutex, Unlock() wakes up the blocking threads and it will execute. It is such a simple course! But when using a Semaphore, each threads will use atomic P() and V() operations. We can see these operations in the code "s.sem_num = 0;", "s.sem_op = -1(1)", "s.sem_flg = 0;". And it reinitialize the value of semid which means the value of semaphore id with "semop(semid, &s, 1);". A series of course is more complex than Mutex and it might affect the delaying times of Execution.



### thread-safe-counter
