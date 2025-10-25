#include "philo.h"

static int ft_valid_args(int ac, char **av) {
  int i;
  int j;
  int value;
  if (ac < 5 || ac > 6) {
    printf("Error: Wrong number of arguments\n");
    printf("Usage: ./philo number_of_philosophers time_to_die ");
    printf("time_to_eat time_to_sleep ");
    printf("[number_of_times_each_philosopher_must_eat]\n");
    return (0);
  }
  i = 1;
  while (i < ac) {
    j = 0;
    while (av[i][j]) {
      if (!ft_isdigit(av[i][j])) {
        return (printf("Error: Invalid argument \n"), 0);
      }
      j++;
    }
    value = ft_atoi(av[i]);
    if (value <= 0) {
      return (printf("Error: Arguments must be positive integers\n"), 0);
    }
    i++;
  }
  return (1);
}

static int ft_create_threads(t_table *table, t_philo *philos) {
  int i;

  pthread_t monitor;
  table->philos = philos;
  i = 0;
  while (i < table->num_philos) {
    if (pthread_create(&philos[i].thread, NULL, ft_philo_routine, &philos[i]) !=
        0) {
      return (0);
    }
    i++;
  }
  if (pthread_create(&monitor, NULL, ft_monitor_routine, table) != 0) {
    return (0);
  }
  pthread_join(monitor, NULL);
  i = 0;
  while (i < table->num_philos) {
    pthread_join(philos[i].thread, NULL);
    i++;
  }
  return (1);
}

int main(int ac, char **av) {
  t_table table;
  t_philo *philos;

  if (!ft_valid_args(ac, av))
    return 1;
  if (!ft_init_table(ac, av, &table))
    return 1;
  if (!ft_init_forks(&table)) {
    ft_clean(&table, NULL);
    return 1;
  }
  if (!ft_init_philos(&table, &philos)) {
    ft_clean(&table, NULL);
    return 1;
  }
  ft_init_philo_data(&table, philos);
  if (!ft_create_threads(&table, philos)) {
    ft_clean(&table, philos);
    return 1;
  }
  ft_clean(&table, philos);
  return 0;
}
