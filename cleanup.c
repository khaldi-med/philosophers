#include "philo.h"

static void destroy_mutexes(t_table *table, t_philo *philos)
{
  int index;

  index = 0;
  while (index < table->num_philos)
  {
    pthread_mutex_destroy(&table->forks[index].mutex);
    pthread_mutex_destroy(&philos[index].meal_mutex);
    index++;
  }
  pthread_mutex_destroy(&table->stop_mutex);
  pthread_mutex_destroy(&table->print_mutex);
}

void ft_clean(t_table *table, t_philo *philos)
{
  destroy_mutexes(table, philos);
  free(table->forks);
  free(philos);
}
