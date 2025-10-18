#include "philo.h"

void ft_print_status(t_philo *philo, const char *status)
{
  long long timestamp;

  pthread_mutex_lock(&philo->table->print_mutex);
  if (!philo->table->simulation_stop)
  {
    timestamp = ft_get_current_time() - philo->table->start_time;
    printf("%lld %d %s\n", timestamp, philo->id, status);
  }
  pthread_mutex_unlock(&philo->table->print_mutex);
}

void ft_print_death(t_philo *philo)
{
  long long timestamp;

  timestamp = ft_get_current_time() - philo->table->start_time;
  pthread_mutex_lock(&philo->table->print_mutex);
  if (!philo->table->simulation_stop)
  {
    printf("%lld %d died\n", timestamp, philo->id);
  }
  pthread_mutex_unlock(&philo->table->print_mutex);
}
