/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:44:35 by mohkhald          #+#    #+#             */
/*   Updated: 2025/10/28 01:44:37 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_philo *philo)
{
	ft_prints_status(philo, "is thinking");
}

void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		ft_prints_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		ft_prints_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		ft_prints_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mutex);
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
