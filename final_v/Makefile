NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
RM = rm -f

SRCS = main.c init.c action.c routine.c monitor.c utils.c clean.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re