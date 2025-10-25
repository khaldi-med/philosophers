#include "philo.h"

void ft_think(t_philo *philo) { ft_prints_status(philo, "is thinking"); }

static void ft_interruptible_sleep(t_philo *philo, long long duration_ms) {
  long long start_time = ft_get_current_time();
  long long target_time = start_time + duration_ms;
  int death_found = 0;
  
  while (ft_get_current_time() < target_time) {
    pthread_mutex_lock(&philo->table->stop_mutex);
    death_found = philo->table->death_flag;
    pthread_mutex_unlock(&philo->table->stop_mutex);
    if (death_found) {
      return;
    }
    usleep(1000);
  }
}

void ft_take_forks(t_philo *philo) {
  if (philo->id % 2 == 0) {
    pthread_mutex_lock(&philo->right_fork->mutex);
    ft_prints_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->left_fork->mutex);
    ft_prints_status(philo, "has taken a fork");
  } else {
    usleep(1000);
    pthread_mutex_lock(&philo->left_fork->mutex);
    ft_prints_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->right_fork->mutex);
    ft_prints_status(philo, "has taken a fork");
  }
}

void ft_eat(t_philo *philo) {
  ft_prints_status(philo, "is eating");
  pthread_mutex_lock(&philo->table->meal_mutex);
  philo->last_meal_time = ft_get_current_time();
  philo->meals_eaten++;
  pthread_mutex_unlock(&philo->table->meal_mutex);
  ft_interruptible_sleep(philo, philo->table->time_to_eat);
}

void ft_put_down_forks(t_philo *philo) {
  pthread_mutex_unlock(&philo->left_fork->mutex);
  pthread_mutex_unlock(&philo->right_fork->mutex);
}

void ft_sleep(t_philo *philo) {
  ft_prints_status(philo, "is sleeping");
  ft_interruptible_sleep(philo, philo->table->time_to_sleep);
}
