#include "philo.h"

static int has_one_philosopher(t_philo *philo)
{
  if (philo->table->num_philos == 1)
  {
    pthread_mutex_lock(&philo->left_f->mutex);
    ft_print_status(philo, "has taken a fork");
    ft_msleep(philo, philo->table->time_to_die);
    pthread_mutex_unlock(&philo->left_f->mutex);
    return (1);
  }
  return (0);
}

void *ft_routine(void *arg)
{
  t_philo *philo;

  philo = (t_philo *)arg;
  if (has_one_philosopher(philo))
    return (NULL);
  if (philo->id % 2 == 0)
    usleep(STAGGER_US);
  while (!ft_simulation_stop(philo))
  {
    ft_philo_think(philo);
    ft_philo_take_fork(philo);
    ft_philo_eat(philo);
    ft_philo_puts_fork(philo);
    ft_philo_sleep(philo);
  }
  return (NULL);
}
