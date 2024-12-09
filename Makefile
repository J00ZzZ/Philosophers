NAME = philo

CC = gcc

RM = rm -f

SRC = philo.c \

CFLAGS = -Wall -Werror -Wextra

OPTION = -I ./

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(OPTION) -o $(NAME)
	@echo "\033[92m--Philo Compiled--\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) $(OPTION) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean 
	@$(RM) $(NAME)
	@echo "\033[92m--Philo Cleaned--\033[0m"

re: fclean all

.PHONY: all clean fclean re