CFLAGS := -Wall -Wextra -Werror
CFILES := src/main.c src/parse.c src/init.c src/utils.c src/philosophize.c src/forks.c
OFILES := $(CFILES:.c=.o)
INCLUDE := include
NAME := philo

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME) -pthread

%.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE) $^ -o $@ -g -pthread

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re