/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:50:58 by mohkhald          #+#    #+#             */
/*   Updated: 2025/10/28 01:44:47 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutexes(t_table *table, t_philo *philos)
{
	int	i;

	(void)philos;
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	if (table->forks)
	{
		i = 0;
		while (i < table->num_philos)
		{
			pthread_mutex_destroy(&table->forks[i].mutex);
			i++;
		}
	}
}

void	ft_clean(t_table *table, t_philo *philos)
{
	ft_destroy_mutexes(table, philos);
	if (table->forks)
		free(table->forks);
	if (philos)
		free(philos);
}
