#include "philo.h"

long ft_get_current_time(void)
{
  struct timeval now;

  gettimeofday(&now, NULL);
  return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int ft_atoi(const char *str)
{
  unsigned int number;
  char *cursor;

  cursor = (char *)str;
  number = 0;
  while ((*cursor >= 9 && *cursor <= 13) || *cursor == ' ')
    cursor++;
  if (*cursor == '+' || *cursor == '-')
  {
    if (*cursor == '-')
    {
      write(2, "the arguments not valid\n", 25);
      exit(1);
    }
    cursor++;
  }
  while (*cursor >= '0' && *cursor <= '9')
  {
    number = (number * 10) + (*cursor - '0');
    cursor++;
  }
  return ((int)number);
}
