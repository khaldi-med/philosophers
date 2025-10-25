/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:52:10 by mohkhald          #+#    #+#             */
/*   Updated: 2025/10/23 16:52:13 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_philo_routine(void *arg) {
  t_philo *philo;

  philo = (t_philo *)arg;
  if (philo->table->num_philos == 1) {
    ft_prints_status(philo, "has taken a fork");
    usleep(philo->table->time_to_die * 1000);
    return (NULL);
  }
  if (philo->id % 2 == 0)
    ft_sleep(philo);
    //usleep(philo->table->time_to_sleep * 1000);
  while (!ft_simulation_stopped(philo)) {
    ft_think(philo);
    if (ft_simulation_stopped(philo))
      break;
    ft_take_forks(philo);
    if (ft_simulation_stopped(philo)) {
      ft_put_down_forks(philo);
      break;
    }
    ft_eat(philo);
    ft_put_down_forks(philo);
    if (ft_simulation_stopped(philo))
      break;
    ft_sleep(philo);
  }
  return (NULL);
}

void *ft_memset(void *block, int c, size_t size) {
  unsigned char *str;

  str = block;
  while (size--) {
    *str++ = (unsigned char)c;
  }
  return (block);
}
