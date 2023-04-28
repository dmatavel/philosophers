SRC_PATH = src/
SRCS = $(shell find $(SRC_PATH) -name "*.c")
OBJS = $(SRCS:.c=.o)
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

