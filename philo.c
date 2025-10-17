#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

void philo_routine(void *arg) { t_philo *philo = (t_philo *)arg; }

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
	{
		printf("arguments not valid");
		return (0);
	}
	table.num_philos = ft_atoi(av[1]);
	table.time_to_die = ft_atoi(av[2]);
	table.time_to_eat = ft_atoi(av[3]);
	table.time_to_sleep = ft_atoi(av[4]);
	table.num_eat_count = -1;
	if (ac == 6)
		table.num_eat_count = ft_atoi(av[5]);
	table.forks = malloc(sizeof(t_fork) * table.num_philos);
	for (int i = 0; i < table.num_philos; i++)
	{
		table.forks[i].id = i;
	}
	philos = malloc(sizeof(t_philo) * table.num_philos);
	for (int i = 0; i < table.num_philos; i++)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].table = &table;
		philos[i].left_f = &table.forks[i];
		philos[i].right_f = &table.forks[(i + 1) % table.num_philos];
		printf("philo num: %d\n", philos[i].id);
		printf("philo num meals_eaten: %d\n", philos[i].meals_eaten);
		printf("philo %d has fork %d and %d\n", philos[i].id,
			   philos[i].left_f->id,
			   philos[i].right_f->id);
	}
	for (int i = 0; i < table.num_philos; i++)
	{
		pthread_create(philos[i].thread, NULL, philo_routine, &philos[i]);
	}
	return (0);
}