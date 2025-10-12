#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// This is the function the thread will run.
// Every philosopher will have a function like this.
void *routine(void *arg) {
  pthread_t id = pthread_self();
  printf("thread id: %lu\n", id);
  char *msg = (char *)arg;
  printf("%s\n", msg);
  sleep(1);
  printf("Thread is finishing.\n");
  return (NULL);
}

int main(void) {
  pthread_t main_id =
      pthread_self(); // This variable will hold the thread's ID.
  printf("main thread id %lu\n", main_id);
  pthread_t t1;
  // Create the thread. It will start running the 'routine' function.
  if (pthread_create(&t1, NULL, &routine, "Hello from thread") != 0)
    return (1); // Error handling

  // Wait for the thread 't1' to finish its work before the main function exits.
  if (pthread_join(t1, NULL) != 0)
    return (2); // Error handling

  printf("Main function finished.\n");
  return (0);
}
