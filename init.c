#include "philo.h"

int ft_init_table(t_table *table)
{
  table->start_time = ft_get_current_time();
  table->simulation_stop = 0;
  if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
    return (1);
  if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
    return (1);
  return (0);
}

static int init_forks(t_table *table)
{
  int index;

  index = 0;
  while (index < table->num_philos)
  {
    table->forks[index].id = index;
    if (pthread_mutex_init(&table->forks[index].mutex, NULL) != 0)
      return (1);
    index++;
  }
  return (0);
}

int ft_init_philos(t_philo *philos, t_table *table)
{
  int index;

  if (init_forks(table))
    return (1);
  index = 0;
  while (index < table->num_philos)
  {
    philos[index].id = index + 1;
    philos[index].meals_eaten = 0;
    philos[index].table = table;
    philos[index].left_f = &table->forks[index];
    philos[index].right_f = &table->forks[(index + 1) % table->num_philos];
    if (pthread_mutex_init(&philos[index].meal_mutex, NULL) != 0)
      return (1);
    philos[index].last_meal_time = table->start_time;
    index++;
  }
  return (0);
}

int ft_start_threads(t_philo *philos, t_table *table)
{
  int index;

  index = 0;
  while (index < table->num_philos)
  {
    if (pthread_create(&philos[index].thread, NULL, ft_routine, &philos[index]) != 0)
    {
      printf("Error: Failed to create thread\n");
      return (1);
    }
    index++;
  }
  return (0);
}
