#include "philo.h"

/*check the flag for simulation stats*/
int ft_simulation_stop(t_philo *philo) {
  int stop;

  pthread_mutex_lock(&philo->table->stop_mutex);
  stop = philo->table->simulation_stop;
  pthread_mutex_unlock(&philo->table->stop_mutex);
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
    pthread_mutex_lock(&philo->left_f->mutex);
    ft_print_status(philo, "has taken a fork\n");
  } else {
    pthread_mutex_lock(&philo->left_f->mutex);
    ft_print_status(philo, "has taken a fork\n");
    pthread_mutex_lock(&philo->right_f->mutex);
    ft_print_status(philo, "has taken a fork\n");
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
void ft_philo_think(t_philo *philo) { ft_print_status(philo, "is thinking\n"); }

/*puts the fork func*/
void ft_philo_puts_fork(t_philo *philo) {
  if (philo->id % 2 == 0) {
    pthread_mutex_unlock(&philo->left_f->mutex);
    pthread_mutex_unlock(&philo->right_f->mutex);
  } else {
    pthread_mutex_unlock(&philo->right_f->mutex);
    pthread_mutex_unlock(&philo->left_f->mutex);
  }
}

/*sleep function*/
void ft_philo_sleep(t_philo *philo) {
  ft_print_status(philo, "is sleeping\n");
  usleep(philo->table->time_to_die * 1000);
}

/*routin function*/
void *ft_routine(void *arg) {
  t_philo *philo;

  philo = (t_philo *)arg;
  if (philo->table->num_philos == 1) {
    ft_print_status(philo, "has taken a fork\n");
    usleep(philo->table->time_to_die * 100);
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

// init philos
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

// clean the program
void ft_clean(t_table *table, t_philo *philo) {
  int i;

  i = 0;
  while (i < table->num_philos) {
    pthread_mutex_destroy(&table->forks->mutex);
    pthread_mutex_destroy(&philo[i].meal_mutex);
  }
  pthread_mutex_destroy(&table->stop_mutex);
  free(table->forks);
  free(philo);
}

// init theads
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
  pthread_mutex_lock(&table->stop_mutex);
  table->simulation_stop = 0;
  pthread_mutex_unlock(&table->stop_mutex);
  ft_clean(table, philos);
  return (0);
}
/*check if philo is death*/
int ft_check_philosopher_death(t_philo *philo) {
  long long current_time;
  long long last_meal;
  long long time_since_meal;

  current_time = ft_get_current_time();
  pthread_mutex_lock(&philo->meal_mutex);
  last_meal = philo->last_meal_time;
  pthread_mutex_unlock(&philo->meal_mutex);
  time_since_meal = current_time - last_meal;
  if (time_since_meal > philo->table->time_to_die) {
    return (1);
  }
  return (0);
}

// print the death philo
void ft_print_death(t_philo *philo) {
  long long timestamp;

  timestamp = ft_get_current_time() - philo->table->start_time;
  printf("%lld %d died\n", timestamp, philo->id);
}

/*is the philos eating enough*/
int ft_is_eat_num(t_table *table, t_philo *philos) {
  int i;
  int count;

  i = 0;
  count = 0;
  if (table->num_eat_count == -1) {
    return (0);
  }
  while (i < table->num_philos) {
    pthread_mutex_lock(&philos[i].meal_mutex);
    if (philos[i].meals_eaten >= table->num_eat_count)
      count++;
    pthread_mutex_unlock(&philos[i].meal_mutex);
    i++;
  }
  if (count == table->num_philos) {
    return (1);
  }
  return (0);
}

void *ft_scan_of_threads(void *arg) {
  t_table *table;
  t_philo *philos;
  int i;

  table = (t_table *)arg;
  philos = table->philos;
  while (1) {
    i = 0;
    while (i < table->num_philos) {
      if (ft_check_philosopher_death(&philos[i])) {
        ft_print_death(&philos[i]);
        pthread_mutex_lock(&table->stop_mutex);
        table->simulation_stop = 1;
        pthread_mutex_unlock(&table->stop_mutex);
        return (NULL);
      }
      i++;
    }
    if (ft_is_eat_num(table, philos)) {
      pthread_mutex_lock(&table->stop_mutex);
      table->simulation_stop = 1;
      pthread_mutex_unlock(&table->stop_mutex);
      return (NULL);
    }
    usleep(1000);
  }
  return (NULL);
}

/*main  function*/
int main(int ac, char **av) {
  t_table table;
  t_philo *philos;
  pthread_t sacn_thread;
  int i;

  if (ac < 5 || ac > 6) {
    printf("arguments not valid");
    return (0);
  }
  table.philos = philos;
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
  pthread_create(&sacn_thread, NULL, ft_scan_of_threads, &table);
  pthread_join(sacn_thread, NULL);
  i = 0;
  while (i < table.num_philos) {
    pthread_join(philos[i].thread, NULL);
    i++;
  }
  ft_clean(&table, philos);
  return (0);
}
