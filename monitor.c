#include "philo.h"

int ft_simulation_stop(t_philo *philo)
{
  int stop;

  pthread_mutex_lock(&philo->table->stop_mutex);
  stop = philo->table->simulation_stop;
  pthread_mutex_unlock(&philo->table->stop_mutex);
  return (stop);
}

int ft_check_philosopher_death(t_philo *philo)
{
  long long now;
  long long last;

  now = ft_get_current_time();
  pthread_mutex_lock(&philo->meal_mutex);
  last = philo->last_meal_time;
  pthread_mutex_unlock(&philo->meal_mutex);
  if ((now - last) > philo->table->time_to_die)
    return (1);
  return (0);
}

int ft_is_eat_num(t_table *table, t_philo *philos)
{
  int index;
  int count;

  index = 0;
  count = 0;
  if (table->num_eat_count == -1)
    return (0);
  while (index < table->num_philos)
  {
    pthread_mutex_lock(&philos[index].meal_mutex);
    if (philos[index].meals_eaten >= table->num_eat_count)
      count++;
    pthread_mutex_unlock(&philos[index].meal_mutex);
    index++;
  }
  if (count == table->num_philos)
    return (1);
  return (0);
}

static int monitor_scan_deaths(t_table *table, t_philo *philos)
{
  int index;

  index = 0;
  while (index < table->num_philos)
  {
    if (ft_check_philosopher_death(&philos[index]))
    {
      ft_print_death(&philos[index]);
      pthread_mutex_lock(&table->stop_mutex);
      table->simulation_stop = 1;
      pthread_mutex_unlock(&table->stop_mutex);
      return (1);
    }
    index++;
  }
  return (0);
}

static int monitor_check_goal_or_stop(t_table *table, t_philo *philos)
{
  int stop;

  if (ft_is_eat_num(table, philos))
  {
    pthread_mutex_lock(&table->stop_mutex);
    table->simulation_stop = 1;
    pthread_mutex_unlock(&table->stop_mutex);
    return (1);
  }
  pthread_mutex_lock(&table->stop_mutex);
  stop = table->simulation_stop;
  pthread_mutex_unlock(&table->stop_mutex);
  if (stop)
  {
    return (1);
  }
  return (0);
}

void *ft_scan_of_threads(void *arg)
{
  t_table *table;
  t_philo *philos;

  table = (t_table *)arg;
  philos = table->philos;
  while (1)
  {
    if (monitor_scan_deaths(table, philos))
    {
      return (NULL);
    }
    if (monitor_check_goal_or_stop(table, philos))
    {
      return (NULL);
    }
    usleep(MONITOR_SLEEP_US);
  }
  return (NULL);
}
