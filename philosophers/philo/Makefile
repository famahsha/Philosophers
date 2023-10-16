NAME = philo

CFLAGS = -Wall -Werror -Wextra
CC = cc -pthread

SRCS = main.c \
		utils.c \
		initialize.c \
		philoroutine.c \
		phases.c \
		check_status.c \
		free.c \



OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
