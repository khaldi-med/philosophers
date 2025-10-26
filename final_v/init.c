#include "philo.h"

int ft_init_table(int ac, char **av, t_table *table) {
  table->num_philos = ft_atoi(av[1]);
  table->time_to_die = ft_atoi(av[2]);
  table->time_to_eat = ft_atoi(av[3]);
  table->time_to_sleep = ft_atoi(av[4]);
  table->must_eat_count = -1;
  if (ac == 6)
    table->must_eat_count = ft_atoi(av[5]);
  table->simulation_stop_flag = 0;
  if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
    return (0);
  if (pthread_mutex_init(&table->stop_mutex, NULL) != 0) {
    pthread_mutex_destroy(&table->print_mutex);
    return (0);
  }
  if (pthread_mutex_init(&table->meal_mutex, NULL) != 0) {
    pthread_mutex_destroy(&table->print_mutex);
    pthread_mutex_destroy(&table->stop_mutex);
    return (0);
  }
  return (1);
}

int ft_init_forks(t_table *table) {
  int i;

  table->forks = malloc(sizeof(t_fork) * table->num_philos);
  if (!table->forks)
    return (0);
  i = 0;
  while (i < table->num_philos) {
    table->forks[i].id = i + 1;
    if (pthread_mutex_init(&table->forks[i].mutex, NULL) != 0) {
      while (i-- > 0)
        pthread_mutex_destroy(&table->forks[i].mutex);
      free(table->forks);
      table->forks = NULL;
      return (0);
    }
    i++;
  }
  return (1);
}

int ft_init_philos(t_table *table, t_philo **philos) {
  int i;

  *philos = malloc(sizeof(t_philo) * table->num_philos);
  if (!*philos)
    return (0);
  i = 0;
  while (i < table->num_philos) {
    (*philos)[i].id = i + 1;
    (*philos)[i].meals_eaten = 0;
    (*philos)[i].last_meal_time = 0;
    (*philos)[i].table = table;
    i++;
  }
  return (1);
}
void ft_init_philo_data(t_table *table, t_philo *philos) {
  int i;

  table->start_time = ft_get_current_time();
  i = 0;
  while (i < table->num_philos) {
    philos[i].last_meal_time = table->start_time;
    philos[i].left_fork = &table->forks[i];
    philos[i].right_fork = &table->forks[(i + 1) % table->num_philos];
    i++;
  }
}
