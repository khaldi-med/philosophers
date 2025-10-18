#include "philo.h"

long ft_get_current_time(void) {
  struct timeval t_value;

  gettimeofday(&t_value, NULL);
  return ((t_value.tv_sec * 1000) + (t_value.tv_usec / 1000));
}

int ft_atoi(const char *str) {
  unsigned int n;
  char *s;

  s = (char *)str;
  n = 0;
  while ((*s >= 9 && *s <= 13) || *s == ' ')
    s++;
  if (*s == '+' || *s == '-') {
    if (*s == '-') {
      write(2, "the arguments not valid\n", 25);
      exit(1);
    }
  }
  while (*s >= '0' && *s <= '9') {
    n = (n * 10) + (*s - '0');
    s++;
  }
  return (n);
}
