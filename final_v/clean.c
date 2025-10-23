#include "philo.h"

void ft_destroy_mutexes(t_table *table, t_philo *philos) {
  int i;

  (void)philos;
  pthread_mutex_destroy(&table->print_mutex);
  pthread_mutex_destroy(&table->stop_mutex);
  pthread_mutex_destroy(&table->meal_mutex);
  if (table->forks) {
    i = 0;
    while (i < table->num_philos) {
      pthread_mutex_destroy(&table->forks[i].mutex);
      i++;
    }
  }
}

void ft_clean(t_table *table, t_philo *philos) {
  ft_destroy_mutexes(table, philos);
  if (table->forks)
    free(table->forks);
  if (philos)
    free(philos);
}