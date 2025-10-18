#ifndef PHILO_H
#define PHILO_H

/* main library */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define MS_TO_US 1000
#define STAGGER_US 15000
#define MONITOR_SLEEP_US 1000
#define ARG_MIN 5
#define ARG_MAX 6
/* fork  struct */
typedef struct s_fork {
  pthread_mutex_t mutex;
  int id;
} t_fork;

/* forward declaration to allow references in t_table */
struct s_philo;
typedef struct s_philo t_philo;

typedef struct s_table {
  int num_philos;
  int time_to_die;
  int time_to_eat;
  int time_to_sleep;
  int num_eat_count;
  int simulation_stop;
  long long start_time;
  pthread_mutex_t stop_mutex;
  pthread_mutex_t print_mutex;
  t_philo *philos;
  t_fork *forks;
} t_table;

/* philo struct */
struct s_philo {
  int id;
  int meals_eaten;
  long long last_meal_time;
  pthread_mutex_t meal_mutex;
  t_fork *left_f;
  t_fork *right_f;
  t_table *table;
  pthread_t thread;
};

/* table struct */
/* my functions */
int ft_atoi(const char *str);
long ft_get_current_time(void);
#endif
void ft_msleep(t_philo *philo, int milliseconds);

/* init */
int ft_init_table(t_table *table);
int ft_init_philos(t_philo *philos, t_table *table);
int ft_start_threads(t_philo *philos, t_table *table);

/* routine and actions */
void *ft_routine(void *arg);
void ft_philo_think(t_philo *philo);
void ft_philo_eat(t_philo *philo);
void ft_philo_sleep(t_philo *philo);

/* forks */
void ft_philo_take_fork(t_philo *philo);
void ft_philo_puts_fork(t_philo *philo);

/* monitor */
int ft_simulation_stop(t_philo *philo);
int ft_check_philosopher_death(t_philo *philo);
void ft_print_death(t_philo *philo);
int ft_is_eat_num(t_table *table, t_philo *philos);
void *ft_scan_of_threads(void *arg);

/* print */
void ft_print_status(t_philo *philo, const char *status);

/* cleanup */
void ft_clean(t_table *table, t_philo *philo);
