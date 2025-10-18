#include "philo.h"
#include <stdio.h>
#include <time.h>

/*check the flag for simulation stats*/
int ft_simulation_stop(t_philo *philo) {
  int stop;

  stop = philo->table->simulation_stop;
  return (stop);
}

/*print status of philo function*/
void ft_print_status(t_philo *philo, char *status) {
  long long timestamp;

  if (philo->table->simulation_stop) {
    return;
  }
  timestamp = ft_get_current_time() - philo->table->start_time;
  printf(" %lld %d %s", timestamp, philo->id, status);
}

/*take fork function*/
void ft_philo_take_fork(t_philo *philo) {
  if (philo->id % 2 == 0) {
    ft_print_status(philo, "philo taken right fork");
    ft_print_status(philo, "philo taken leftchar *status fork");
  } else {
    ft_print_status(philo, "philo taken left fork");
    ft_print_status(philo, "philo taken right fork");
  }
}

/*eating function*/
void ft_philo_eat(t_philo *philo) {
  ft_print_status(philo, "is eating");
  philo->last_meal_time = ft_get_current_time();
  philo->meals_eaten++;
  usleep(philo->table->time_to_eat * 1000);
}

/*think function*/
void ft_philo_think(t_philo *philo) {
  ft_print_status(philo, "Philo is thinking");
}

/*puts the fork func*/
void ft_philo_puts_fork(t_philo *philo) {
  if (philo->id % 2 == 0) {
    /* TODO:  <18-10-25, unlock mutex> */
  } else {
    /* TODO:  <18-10-25,unlock mutex> */
  }
}

/*sleep function*/
void ft_philo_sleep(t_philo *philo) {
  ft_print_status(philo, "is sleep");
  usleep(philo->table->time_to_die * 1000);
}

/*routin function*/
void *ft_routine(void *arg) {
  t_philo *philo;

  philo = (t_philo *)arg;
  if (philo->table->num_philos == 1) {
    ft_print_status(philo, "has take a fork");
    usleep(philo->table->time_to_die * 1000);
    return (NULL);
  }
  if (philo->id % 2 == 0)
    usleep(15000);
  while (!ft_simulation_stop(philo)) {
    /* TODO:  <18-10-25, creat_funs> */
    ft_philo_think(philo);
    ft_philo_take_fork(philo);
    ft_philo_eat(philo);
    ft_philo_puts_fork(philo);
    ft_philo_sleep(philo);
  }
  return (NULL);
}

/*main  function*/
int main(int ac, char **av) {
  t_table table;
  t_philo *philos;

  if (ac < 5 || ac > 6) {
    printf("arguments not valid");
    return (0);
  }
  table.num_philos = ft_atoi(av[1]);
  table.time_to_die = ft_atoi(av[2]);
  table.time_to_eat = ft_atoi(av[3]);
  table.time_to_sleep = ft_atoi(av[4]);
  table.num_eat_count = -1;
  if (ac == 6)
    table.num_eat_count = ft_atoi(av[5]);
  table.forks = malloc(sizeof(t_fork) * table.num_philos);
  for (int i = 0; i < table.num_philos; i++) {
    table.forks[i].id = i;
  }
  philos = malloc(sizeof(t_philo) * table.num_philos);
  for (int i = 0; i < table.num_philos; i++) {
    philos[i].id = i + 1;
    philos[i].meals_eaten = 0;
    philos[i].table = &table;
    philos[i].left_f = &table.forks[i];
    philos[i].right_f = &table.forks[(i + 1) % table.num_philos];
    /* printf("philo num: %d\n", philos[i].id); */
    /* printf("philo num meals_eaten: %d\n", philos[i].meals_eaten); */
    /* printf("philo %d has fork %d and %d\n", philos[i].id,
     * philos[i].left_f->id, */
    /* philos[i].right_f->id); */
  }
  table.start_time = ft_get_current_time();
  table.simulation_stop = 0;
  /* printf("the current time in milliscond: %lld\n", table.start_time); */
  for (int i = 0; i < table.num_philos; i++) {
    /* pthread_create(&philos[i].thread, NULL, routine, &philos[i]); */
  }
  return (0);
}
