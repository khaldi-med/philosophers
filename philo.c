#include "philo.h"
#include <pthread.h>

/*check the flag for simulation stats*/
int ft_simulation_stop(t_philo *philo) {
  int stop;

  stop = philo->table->simulation_stop;
  return (stop);
}

/*print status of philo function*/
void ft_print_status(t_philo *philo, char *status) {
  long long timestamp;

  if (philo->table->simulation_stop) {
    return;
  }
  timestamp = ft_get_current_time() - philo->table->start_time;
  printf(" %lld %d %s\n", timestamp, philo->id, status);
}

/*take fork function*/
void ft_philo_take_fork(t_philo *philo) {
  if (philo->id % 2 == 0) {
    pthread_mutex_lock(&philo->right_f->mutex);
    ft_print_status(philo, "philo taken right fork\n");
    pthread_mutex_unlock(&philo->right_f->mutex);
    pthread_mutex_lock(&philo->left_f->mutex);
    ft_print_status(philo, "philo taken left fork\n");
    pthread_mutex_unlock(&philo->left_f->mutex);
  } else {
    pthread_mutex_lock(&philo->left_f->mutex);
    ft_print_status(philo, "philo taken left fork\n");
    pthread_mutex_unlock(&philo->left_f->mutex);
    pthread_mutex_lock(&philo->right_f->mutex);
    ft_print_status(philo, "philo taken right fork\n");
    pthread_mutex_unlock(&philo->right_f->mutex);
  }
}

/*eating function*/
void ft_philo_eat(t_philo *philo) {
  ft_print_status(philo, "is eating\n");
  philo->last_meal_time = ft_get_current_time();
  philo->meals_eaten++;
  usleep(philo->table->time_to_eat * 1000);
}

/*think function*/
void ft_philo_think(t_philo *philo) {
  ft_print_status(philo, "Philo is thinking\n");
}

/*puts the fork func*/
void ft_philo_puts_fork(t_philo *philo) {
  if (philo->id % 2 == 0) {
    /* TODO:  <18-10-25, unlock mutex> */
  } else {
    /* TODO:  <18-10-25,unlock mutex> */
  }
}

/*sleep function*/
void ft_philo_sleep(t_philo *philo) {
  ft_print_status(philo, "is sleep\n");
  usleep(philo->table->time_to_die * 1000);
}

/*routin function*/
void *ft_routine(void *arg) {
  t_philo *philo;

  philo = (t_philo *)arg;
  if (philo->table->num_philos == 1) {
    ft_print_status(philo, "has take a fork\n");
    usleep(philo->table->time_to_die * 1000);
    return (NULL);
  }
  if (philo->id % 2 == 0)
    usleep(15000);
  while (!ft_simulation_stop(philo)) {
    ft_philo_think(philo);
    ft_philo_take_fork(philo);
    ft_philo_eat(philo);
    ft_philo_puts_fork(philo);
    ft_philo_sleep(philo);
  }
  return (NULL);
}

void ft_init_philos(t_philo *philos, t_table *table) {
  int i;
  int j;

  i = 0;
  while (i < table->num_philos) {
    table->forks[i].id = i;
    i++;
  }
  j = 0;
  while (j < table->num_philos) {
    philos[j].id = j + 1;
    philos[j].meals_eaten = 0;
    philos[j].table = table;
    philos[j].left_f = &table->forks[j];
    philos[j].right_f = &table->forks[(j + 1) % table->num_philos];
    j++;
  }
  table->start_time = ft_get_current_time();
  table->simulation_stop = 0;
}

int ft_init_philo_thread(t_philo *philos, t_table *table) {
  int i;

  i = 0;
  while (i < table->num_philos) {
    if (pthread_create(&philos[i].thread, NULL, ft_routine, &philos[i]) != 0) {
      // Handle thread creation error
      printf("Error: Failed to create thread\n");
      return (1);
    }
    i++;
  }
  usleep(500000);
  table->simulation_stop = 0;
  return 0;
}

/*main  function*/
int main(int ac, char **av) {
  t_table table;
  t_philo *philos;

  if (ac < 5 || ac > 6) {
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
  philos = malloc(sizeof(t_philo) * table.num_philos);
  ft_init_philos(philos, &table);
  ft_init_philo_thread(philos, &table);
  return (0);
}
