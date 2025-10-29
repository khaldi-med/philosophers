/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:52:02 by mohkhald          #+#    #+#             */
/*   Updated: 2025/10/28 01:45:21 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					id;
}						t_fork;

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int					num_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	long long			start_time;
	int					simulation_stop_flag;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		meal_mutex;
}						t_table;

struct					s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_table				*table;
	pthread_t			thread;
};

int						ft_init_table(int ac, char **av, t_table *table);
int						ft_init_forks(t_table *table);
int						ft_init_philos(t_table *table, t_philo **philos);
void					ft_init_philo_data(t_table *table, t_philo *philos);
int						ft_atoi(char *str);
int						ft_isdigit(int c);
void					ft_prints_status(t_philo *philo, char *status);
void					*ft_memset(void *block, int c, size_t size);
long long				ft_get_current_time(void);
int						ft_check_philo_death(t_philo *philo);
void					ft_philo_death(t_philo *philo);
int						ft_all_ate_enough(t_table *table, t_philo *philos);
void					*ft_monitor_routine(void *arg);
void					*ft_philo_routine(void *arg);
void					ft_think(t_philo *philo);
void					ft_take_forks(t_philo *philo);
void					ft_sleep(t_philo *philo);
void					ft_eat(t_philo *philo);
void					ft_put_down_forks(t_philo *philo);
void					ft_destroy_mutexes(t_table *table, t_philo *philos);
void					ft_clean(t_table *table, t_philo *philos);
void					ft_set_simulation_stop(t_table *table);
int						ft_simulation_stopped(t_philo *philo);
void					ft_sleep_with_check(t_philo *philo,
							long long timeout_ms);
#endif
