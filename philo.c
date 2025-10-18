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
void ft_print_status(t_philo *philo, const char *status) {
  long long timestamp;

  pthread_mutex_lock(&philo->table->print_mutex);
  if (!philo->table->simulation_stop) {
    timestamp = ft_get_current_time() - philo->table->start_time;
    printf("%lld %d %s\n", timestamp, philo->id, status);
  }
  pthread_mutex_unlock(&philo->table->print_mutex);
}

/* sleep in milliseconds with periodic stop checks */
static void ft_msleep(t_philo *philo, int ms) {
  long long start = ft_get_current_time();
  while (!ft_simulation_stop(philo)) {
    long long now = ft_get_current_time();
    if ((now - start) >= ms)
      break;
    usleep(1000); /* sleep ~1ms granularity */
  }
}

/*take fork function*/
void ft_philo_take_fork(t_philo *philo) {
  t_fork *first;
  t_fork *second;

  if (philo->left_f->id < philo->right_f->id) {
    first = philo->left_f;
    second = philo->right_f;
  } else {
    first = philo->right_f;
    second = philo->left_f;
  }
  pthread_mutex_lock(&first->mutex);
  ft_print_status(philo, "has taken a fork");
  pthread_mutex_lock(&second->mutex);
  ft_print_status(philo, "has taken a fork");
}

/*eating function*/
void ft_philo_eat(t_philo *philo) {
  pthread_mutex_lock(&philo->meal_mutex);
  philo->last_meal_time = ft_get_current_time();
  philo->meals_eaten++;
  pthread_mutex_unlock(&philo->meal_mutex);
  ft_print_status(philo, "is eating");
  ft_msleep(philo, philo->table->time_to_eat);
}

/*think function*/
void ft_philo_think(t_philo *philo) {
  int think_ms;

  ft_print_status(philo, "is thinking");
  /* spread attempts to grab forks to avoid starvation */
  think_ms = (philo->table->time_to_die - philo->table->time_to_eat -
              philo->table->time_to_sleep) /
             2;
  if (think_ms < 0)
    think_ms = 0;
  /* tiny extra offset for even ids */
  if (philo->id % 2 == 0)
    think_ms += 1;
  if (think_ms > 0)
    ft_msleep(philo, think_ms);
}

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
  ft_print_status(philo, "is sleeping");
  ft_msleep(philo, philo->table->time_to_sleep);
}

/*routin function*/
void *ft_routine(void *arg) {
  t_philo *philo;

  philo = (t_philo *)arg;
  if (philo->table->num_philos == 1) {
    pthread_mutex_lock(&philo->left_f->mutex);
    ft_print_status(philo, "has taken a fork");
    usleep(philo->table->time_to_die * 1000);
    pthread_mutex_unlock(&philo->left_f->mutex);
    return (NULL);
  }
  if (philo->id % 2 == 0) {
    usleep(15000);
  }
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
  int idx;

  table->start_time = ft_get_current_time();
  table->simulation_stop = 0;
  pthread_mutex_init(&table->stop_mutex, NULL);
  pthread_mutex_init(&table->print_mutex, NULL);

  idx = 0;
  while (idx < table->num_philos) {
    table->forks[idx].id = idx;
    pthread_mutex_init(&table->forks[idx].mutex, NULL);
    idx++;
  }

  idx = 0;
  while (idx < table->num_philos) {
    philos[idx].id = idx + 1;
    philos[idx].meals_eaten = 0;
    philos[idx].table = table;
    philos[idx].left_f = &table->forks[idx];
    philos[idx].right_f = &table->forks[(idx + 1) % table->num_philos];
    pthread_mutex_init(&philos[idx].meal_mutex, NULL);
    philos[idx].last_meal_time = table->start_time;
    idx++;
  }
}

// clean the program
void ft_clean(t_table *table, t_philo *philo) {
  int idx;

  idx = 0;
  while (idx < table->num_philos) {
    pthread_mutex_destroy(&table->forks[idx].mutex);
    pthread_mutex_destroy(&philo[idx].meal_mutex);
    idx++;
  }
  pthread_mutex_destroy(&table->stop_mutex);
  free(table->forks);
  free(philo);
}

// init theads
int ft_init_philo_thread(t_philo *philos, t_table *table) {
  int idx;

  idx = 0;
  while (idx < table->num_philos) {
    if (pthread_create(&philos[idx].thread, NULL, ft_routine, &philos[idx]) != 0) {
      // Handle thread creation error
      printf("Error: Failed to create thread\n");
      return (1);
    }
    idx++;
  }
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
  pthread_mutex_lock(&philo->table->print_mutex);
  if (!philo->table->simulation_stop) {
    printf("%lld %d died\n", timestamp, philo->id);
  }
  pthread_mutex_unlock(&philo->table->print_mutex);
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
  int idx;

  table = (t_table *)arg;
  philos = table->philos;
  while (1) {
    idx = 0;
    while (idx < table->num_philos) {
      if (ft_check_philosopher_death(&philos[idx])) {
        ft_print_death(&philos[idx]);
        pthread_mutex_lock(&table->stop_mutex);
        table->simulation_stop = 1;
        pthread_mutex_unlock(&table->stop_mutex);
        return (NULL);
      }
      idx++;
    }
    if (ft_is_eat_num(table, philos)) {
      pthread_mutex_lock(&table->stop_mutex);
      table->simulation_stop = 1;
      pthread_mutex_unlock(&table->stop_mutex);
      return (NULL);
    }
    if (table->simulation_stop) {
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
  int idx;

  if (ac < 5 || ac > 6) {
    printf("arguments not valid");
    return (0);
  }
  table.num_philos = ft_atoi(av[1]);
  table.time_to_die = ft_atoi(av[2]);
  table.time_to_eat = ft_atoi(av[3]);
  table.time_to_sleep = ft_atoi(av[4]);
  table.num_eat_count = -1;
  if (ac == 6) {
    table.num_eat_count = ft_atoi(av[5]);
  }
  table.forks = malloc(sizeof(t_fork) * table.num_philos);
  if (!table.forks) {
    perror("malloc forks");
    return (1);
  }
  philos = malloc(sizeof(t_philo) * table.num_philos);
  if (!philos) {
    perror("malloc philos");
    free(table.forks);
    return (1);
  }
  table.philos = philos;
  ft_init_philos(philos, &table);
  ft_init_philo_thread(philos, &table);
  pthread_create(&sacn_thread, NULL, ft_scan_of_threads, &table);
  pthread_join(sacn_thread, NULL);
  idx = 0;
  while (idx < table.num_philos) {
    pthread_join(philos[idx].thread, NULL);
    idx++;
  }
  ft_clean(&table, philos);
  return (0);
}
