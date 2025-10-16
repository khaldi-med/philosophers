#include "philo.h"

#include "philo.h"

int ft_atoi(const char *str) {
  unsigned int n;
  char *s;

  s = (char *)str;
  n = 0;
  while ((*s >= 9 && *s <= 13) || *s == ' ')
    s++;
  if (*s == '+' || *s == '-') {
    if (*s == '-')
      return 1;
    s++;
  }
  while (*s >= '0' && *s <= '9') {
    n = (n * 10) + (*s - '0');
    s++;
  }
  return (n);
}
