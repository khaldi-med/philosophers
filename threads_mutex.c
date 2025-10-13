#include <pthread.h>
#include <stdio.h>

// Let's pretend this is our critical shared data.
// 0 = fork is taken, 1 = fork is available
int fork_is_available = 1;
pthread_mutex_t fork_mutex; // The mutex that will protect our fork

// This function simulates a philosopher trying to take the fork.
void *philosopher_action(void *arg) {
  char *mssg = (char *)arg;
  // --- Lock the mutex before entering the critical section ---
  pthread_mutex_lock(&fork_mutex);
  // --- CRITICAL SECTION START ---
  // Because of the lock, only one thread can be in here at a time.
  if (fork_is_available == 1) {
    printf("%s", mssg);
    fork_is_available = 0; // Take the fork
  } else {
    printf("Philosopher sees fork is NOT available.\n");
  }
  // --- CRITICAL SECTION END ---
  // --- Unlock the mutex so other threads can get in ---
  pthread_mutex_unlock(&fork_mutex);
  return (NULL);
}

int main(void) {
  pthread_t p1, p2;
  // Initialize the mutex before any threads can use it
  pthread_mutex_init(&fork_mutex, NULL);
  // Create two philosophers (threads) that will both try to take the fork
  pthread_create(&p1, NULL, &philosopher_action,
                 "Philosopher 1 sees fork is available, taking it.\n");
  pthread_create(&p2, NULL, &philosopher_action,
                 "Philosopher 2 sees fork is available, taking it.\n");
  // Wait for them to finish
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  // Clean up the mutex at the very end
  pthread_mutex_destroy(&fork_mutex);
  return (0);
}
