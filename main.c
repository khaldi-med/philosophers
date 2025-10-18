#include "philo.h"

static int init_args(t_table *table, int argc, char **argv)
{
  table->num_philos = ft_atoi(argv[1]);
  table->time_to_die = ft_atoi(argv[2]);
  table->time_to_eat = ft_atoi(argv[3]);
  table->time_to_sleep = ft_atoi(argv[4]);
  table->num_eat_count = -1;
  if (argc == ARG_MAX)
    table->num_eat_count = ft_atoi(argv[5]);
  return (0);
}

int main(int argc, char **argv)
{
  t_table table;
  t_philo *philos;
  pthread_t monitor_thread;
  int index;

  if (argc < ARG_MIN || argc > ARG_MAX)
  {
    printf("arguments not valid\n");
    return (0);
  }
  if (init_args(&table, argc, argv))
    return (1);
  table.forks = malloc(sizeof(t_fork) * table.num_philos);
  if (!table.forks)
    return (perror("malloc forks"), 1);
  philos = malloc(sizeof(t_philo) * table.num_philos);
  if (!philos)
    return (perror("malloc philos"), free(table.forks), 1);
  table.philos = philos;
  if (ft_init_table(&table) || ft_init_philos(philos, &table))
    return (free(table.forks), free(philos), 1);
  if (ft_start_threads(philos, &table))
    return (ft_clean(&table, philos), 1);
  pthread_create(&monitor_thread, NULL, ft_scan_of_threads, &table);
  pthread_join(monitor_thread, NULL);
  index = 0;
  while (index < table.num_philos)
  {
    pthread_join(philos[index].thread, NULL);
    index++;
  }
  ft_clean(&table, philos);
  return (0);
}
