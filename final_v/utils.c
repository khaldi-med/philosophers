/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 00:15:12 by mohkhald          #+#    #+#             */
/*   Updated: 2025/10/27 00:15:13 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long long	ft_get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_prints_status(t_philo *philo, char *status)
{
	long long	timestamp;

	timestamp = ft_get_current_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->stop_mutex);
	if (!philo->table->simulation_stop_flag)
		printf("%lld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->table->stop_mutex);
}

int	ft_simulation_stopped(t_philo *philo)
{
	int	stopped;

	pthread_mutex_lock(&philo->table->stop_mutex);
	stopped = philo->table->simulation_stop_flag;
	pthread_mutex_unlock(&philo->table->stop_mutex);
	return (stopped);
}
