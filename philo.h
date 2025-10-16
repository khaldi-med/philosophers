#ifndef PHILO_H
#define PHILO_H

/* main library */
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
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
  int num_eat_count;
  long long start_time;
  t_fork *fork;
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

#endif
