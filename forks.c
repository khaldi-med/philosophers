#include "philo.h"

void ft_philo_take_fork(t_philo *philo)
{
  t_fork *first_fork;
  t_fork *second_fork;

  if (philo->left_f->id < philo->right_f->id)
  {
    first_fork = philo->left_f;
    second_fork = philo->right_f;
  }
  else
  {
    first_fork = philo->right_f;
    second_fork = philo->left_f;
  }
  pthread_mutex_lock(&first_fork->mutex);
  ft_print_status(philo, "has taken a fork");
  pthread_mutex_lock(&second_fork->mutex);
  ft_print_status(philo, "has taken a fork");
}

void ft_philo_puts_fork(t_philo *philo)
{
  pthread_mutex_unlock(&philo->right_f->mutex);
  pthread_mutex_unlock(&philo->left_f->mutex);
}
