#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

typedef struct s_fork {
  int id;
  pthread_mutex_t mutex; // The lock protecting this fork
} t_fork;

typedef struct s_philo {
  int id;
  t_fork *left_fork;
  t_fork *right_fork;
} t_philo;

void take_fork(t_philo *philo, t_fork *fork) {
  // LOCK - only one philosopher can execute this section at a time
  pthread_mutex_lock(&fork->mutex);
  // Critical section - safe now!
  printf("Philosopher %d has taken fork %d\n", philo->id, fork->id);
  // Simulate holding the fork
  usleep(100000); // Hold for 100ms
  // UNLOCK - release so others can take it
  pthread_mutex_unlock(&fork->mutex);
  printf("Philosopher %d released fork %d\n", philo->id, fork->id);
}

void *philosopher_routine(void *arg) {
  t_philo *philo;

  philo = (t_philo *)arg;
  for (int i = 0; i < 3; i++) // Each philosopher tries 3 times
  {
    take_fork(philo, philo->left_fork);
    usleep(50000); // Think for 50ms
  }
  return (NULL);
}

int main(void) {
  t_fork fork;
  t_philo philo1;
  t_philo philo2;

  // One fork shared between two philosophers
  fork.id = 1;
  pthread_mutex_init(&fork.mutex, NULL); // Initialize the lock!
  // Two philosophers
  philo1.id = 1;
  philo2.id = 2;
  philo1.left_fork = &fork;
  philo2.left_fork = &fork;
  philo2.right_fork = NULL;
  philo1.right_fork = NULL;
  pthread_t thread1, thread2;
  // Create threads
  pthread_create(&thread1, NULL, philosopher_routine, &philo1);
  pthread_create(&thread2, NULL, philosopher_routine, &philo2);
  // Wait for completion
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  // Clean up
  pthread_mutex_destroy(&fork.mutex);
  printf("Simulation complete!\n");
  return (0);
}
