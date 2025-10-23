#include "philo.h"

long long ft_get_current_time(void) {
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_prints_status(t_philo *philo, char *status) {
  long long timestamp;

  pthread_mutex_lock(&philo->table->stop_mutex);
  if (philo->table->simulation_stop_flag) {
    pthread_mutex_unlock(&philo->table->stop_mutex);
    return;
  }
  pthread_mutex_unlock(&philo->table->stop_mutex);
  timestamp = ft_get_current_time() - philo->table->start_time;
  pthread_mutex_lock(&philo->table->print_mutex);
  printf("%lld %d %s\n", timestamp, philo->id, status);
  pthread_mutex_unlock(&philo->table->print_mutex);
}

int ft_simulation_stopped(t_philo *philo) {
  int stopped;

  pthread_mutex_lock(&philo->table->stop_mutex);
  stopped = philo->table->simulation_stop_flag;
  pthread_mutex_unlock(&philo->table->stop_mutex);
  return (stopped);
}

int ft_isdigit(int c) { return (c >= '0' && c <= '9'); }


int ft_atoi( char *str) {
  int result;
  int sign;

  result = 0;
  sign = 1;
  while (*str == ' ' || (*str >= 9 && *str <= 13))
    str++;
  if (*str == '-' || *str == '+') {
    if (*str == '-')
      return 1;
    else
      sign = 1;
    str++;
  }
  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }
  return (sign * result);
}
