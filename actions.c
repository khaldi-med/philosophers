#include "philo.h"

void ft_msleep(t_philo *philo, int milliseconds)
{
  long long start_time;
  long long current_time;

  start_time = ft_get_current_time();
  while (!ft_simulation_stop(philo))
  {
    current_time = ft_get_current_time();
    if ((current_time - start_time) >= milliseconds)
    {
      break;
    }
    usleep(MONITOR_SLEEP_US);
  }
}

void ft_philo_eat(t_philo *philo)
{
  pthread_mutex_lock(&philo->meal_mutex);
  philo->last_meal_time = ft_get_current_time();
  philo->meals_eaten++;
  pthread_mutex_unlock(&philo->meal_mutex);
  ft_print_status(philo, "is eating");
  ft_msleep(philo, philo->table->time_to_eat);
}

void ft_philo_think(t_philo *philo)
{
  int think_time;

  ft_print_status(philo, "is thinking");
  think_time = (philo->table->time_to_die - philo->table->time_to_eat - philo->table->time_to_sleep) / 2;
  if (think_time < 0)
  {
    think_time = 0;
  }
  if (philo->id % 2 == 0)
  {
    think_time += 1;
  }
  if (think_time > 0)
  {
    ft_msleep(philo, think_time);
  }
}

void ft_philo_sleep(t_philo *philo)
{
  ft_print_status(philo, "is sleeping");
  ft_msleep(philo, philo->table->time_to_sleep);
}
