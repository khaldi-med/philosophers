/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 01:44:59 by mohkhald          #+#    #+#             */
/*   Updated: 2025/10/28 01:45:01 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_philo_death(t_philo *philo)
{
	long long	time_since_meal;

	pthread_mutex_lock(&philo->table->meal_mutex);
	time_since_meal = ft_get_current_time() - philo->last_meal_time;
	if (time_since_meal > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->meal_mutex);
	return (0);
}

void	ft_philo_death(t_philo *philo)
{
	long long	timestamp;

	timestamp = ft_get_current_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

int	ft_all_ate_enough(t_table *table, t_philo *philos)
{
	int	i;
	int	count;

	if (table->must_eat_count == -1)
		return (0);
	pthread_mutex_lock(&table->meal_mutex);
	count = 0;
	i = 0;
	while (i < table->num_philos)
	{
		if (philos[i].meals_eaten >= table->must_eat_count)
			count++;
		i++;
	}
	pthread_mutex_unlock(&table->meal_mutex);
	if (count == table->num_philos)
	{
		return (1);
	}
	return (0);
}

void	ft_set_simulation_stop(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->simulation_stop_flag = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

void	*ft_monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	usleep(100);
	while (1)
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (ft_check_philo_death(&table->philos[i]))
			{
				ft_set_simulation_stop(table);
				ft_philo_death(&table->philos[i]);
				return (NULL);
			}
			i++;
		}
		if (ft_all_ate_enough(table, table->philos))
		{
			ft_set_simulation_stop(table);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
