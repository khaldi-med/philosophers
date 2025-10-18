#ifndef PHILO_H
#define PHILO_H

/* main library */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/* fork  struct */
typedef struct s_fork {
  pthread_mutex_t mutex;
  int id;
} t_fork;

/* table struct */
typedef struct s_table {
  int num_philos;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int num_eat_count;
  int simulation_stop;
  long long start_time;
  pthread_mutex_t stop_mutex;
  t_fork *forks;
} t_table;

/* philo struct */
typedef struct s_philo {
  int id;
  int meals_eaten;
  long long last_meal_time;
  pthread_mutex_t meal_mutex;
  t_fork *left_f;
  t_fork *right_f;
  t_table *table;
  pthread_t thread;
} t_philo;

/* my functions */
int ft_atoi(const char *str);
long ft_get_current_time(void);
#endif
