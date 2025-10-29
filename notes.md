## What is threads?

* What is a Mutex?

``A mutex (short for Mutual Exclusion) is a digital lock. Its only purpose is to protect a "critical section" of code to ensure that only one thread can execute that section at a time.``

### if you remove thread\_join:
``If you call pthread_create but never call pthread_join, the thread becomes a "zombie thread" - it finishes execution but its resources (thread descriptor, exit status) aren't freed. Additionally, the main program might exit before threads complete their work, causing premature termination. You create a resource leak and lose control over thread completion.``

### Understanding Data Races
* A data race occurs when:
``
* Two or more threads access the same memory location
* At least one access is a write operation
* The accesses happen without synchronization

The result? Undefined behavior - your program might work correctly sometimes, crash other times, or produce wrong results.
``

### why does each fork need its own separate mutex? Why can't all 5 forks share one mutex?
``
Each fork needs its own mutex because different philosophers can use different forks simultaneously. If all 5 forks shared one mutex, only ONE philosopher could hold ANY fork at a time, even though Philosopher 1 using Fork 1 doesn't conflict with Philosopher 3 using Fork 3. This would be unnecessarily restrictive and hurt performance. Each fork is an independent resource that needs independent protection.``

### Checking simulation?

``
**Checking simulation_stopped()** before locking forks prevents a philosopher from trying to acquire locks after death has been announced. Without this check, a philosopher might lock a fork just as the simulation stops, then try to print or continue actions after death is announced, causing incorrect output. It also helps threads exit cleanly when the simulation ends.``


### pthread_create - Creating a Thread

``` 
int pthread_create(pthread_t *thread, 
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *), 
                   void *arg);
Parameters:
- thread: Pointer to store the thread ID
- attr: Thread attributes (usually NULL for default)
- start_routine: The function this thread will run
- arg: Argument to pass to that function
```

### DATA RACE or RACE CONDITION
``when two threads access shared data simultaneously without synchronization, and at least one modifies it.``

### MUTEXES

``programming An object in a program that serves as a lock, used to negotiate mutual exclusion among threads.``


#### Process Control Block (PCB)
``
A process is internally represented by the operating system using a process control block (PCB). It is also known as Task Control Block.

A PCB contains the following information:

Process Identification (process id)
Process State
Process Control Information (Scheduling Information, Program Counter, Process Privileges, CPU Registers, etc)
``
### Multithreading
`` Multithreading refers to the ability of an OS to support multiple, concurrent paths
of execution within a single process.``


