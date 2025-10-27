
#include "philo.h"

static void	ft_sleep_with_check(t_philo *philo, long long timeout_ms)
{
	long long	start_ms;
	long long	deadline;

	start_ms = ft_get_current_time();
	deadline = start_ms + timeout_ms;
	while (ft_get_current_time() < deadline)
	{
		if (ft_simulation_stopped(philo))
		{
			return ;
		}
		usleep(100);
	}
}

void	ft_think(t_philo *philo)
{
	ft_prints_status(philo, "is thinking");
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		ft_prints_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
		ft_prints_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		ft_prints_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		ft_prints_status(philo, "has taken a fork");
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->meal_mutex);
	ft_prints_status(philo, "is eating");
	philo->last_meal_time = ft_get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table->meal_mutex);
	ft_sleep_with_check(philo, philo->table->time_to_eat);
}

void	ft_put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	ft_sleep(t_philo *philo)
{
	ft_prints_status(philo, "is sleeping");
	ft_sleep_with_check(philo, philo->table->time_to_sleep);
}
