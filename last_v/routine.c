/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:52:10 by mohkhald          #+#    #+#             */
/*   Updated: 2025/10/28 01:45:12 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_one_philo(t_philo *philo)
{
	if (philo->table->num_philos == 1)
	{
		ft_think(philo);
		ft_prints_status(philo, "has taken a fork");
		usleep(philo->table->time_to_die * 1000);
		return (1);
	}
	return (0);
}

static void	ft_main_routine_loop(t_philo *philo)
{
	while (!ft_simulation_stopped(philo))
	{
		ft_think(philo);
		if (ft_simulation_stopped(philo))
			break ;
		ft_take_forks(philo);
		if (ft_simulation_stopped(philo))
		{
			ft_put_down_forks(philo);
			break ;
		}
		ft_eat(philo);
		ft_put_down_forks(philo);
		if (ft_simulation_stopped(philo))
			break ;
		ft_sleep(philo);
	}
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (ft_one_philo(philo))
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(100);
	ft_main_routine_loop(philo);
	return (NULL);
}

void	ft_sleep_with_check(t_philo *philo, long long timeout_ms)
{
	long long	start_ms;
	long long	deadline;
	long long	remaining;

	start_ms = ft_get_current_time();
	deadline = start_ms + timeout_ms;
	while (ft_get_current_time() < deadline)
	{
		if (ft_simulation_stopped(philo))
			return ;
		remaining = deadline - ft_get_current_time();
		if (remaining > 10)
			usleep(5000);
		else if (remaining > 0)
			usleep(500);
	}
}

void	*ft_memset(void *block, int c, size_t size)
{
	unsigned char	*str;

	str = block;
	while (size--)
	{
		*str++ = (unsigned char)c;
	}
	return (block);
}
