#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t lock;

void *print(void *arg) {
  char *msg = (char *)arg;
  for (int i = 0; i < 5; i++) {
    pthread_mutex_lock(&lock);
    printf("%s\n", msg);
    pthread_mutex_unlock(&lock);
    sleep(1);
  }
  return (NULL);
}

int main(void) {
  pthread_t thread1, thread2;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&thread1, NULL, print, "thread 1 speaking");
  pthread_create(&thread2, NULL, print, "thread 2 speaking");
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  pthread_mutex_destroy(&lock);
  return (0);
}
