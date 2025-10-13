## What is threads?

* What is a Mutex?
``
A mutex (short for Mutual Exclusion) is a digital lock. Its only purpose is to protect a "critical section" of code to ensure that only one thread can execute that section at a time.
``
* if you remove thread_join:
``If you call pthread_create but never call pthread_join, the thread becomes a "zombie thread" - it finishes execution but its resources (thread descriptor, exit status) aren't freed. Additionally, the main program might exit before threads complete their work, causing premature termination. You create a resource leak and lose control over thread completion.``
