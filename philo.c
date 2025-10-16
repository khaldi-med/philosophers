#include "philo.h"

int main(int ac, char **av) {
  if (ac < 4 || ac > 5) {
    printf("arguments not valid");
    return 0;
  }
  t_table *table;
  t_philo philo;

  t_table->num_philos = ft_atoi(av[1]);
  t_table->time_to_die = ft_atoi(av[2]);
  t_table->time_to_eat = ft_atoi(av[3]);
  t_table->num_eat_count = ft_atoi(av[4]);

  return (0);
}
