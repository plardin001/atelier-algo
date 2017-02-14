NAME=TAD1
NAME_DEBUG=test_unitaire
CC=gcc
FLAGS= -g -std=c99 -c -Wall -Wextra
SRC=set_sentinel.c	\
	test_unitaire.c
SRC2=set_sentinel_d.c\
	test_unitaire2.c
OBJ= $(SRC:.c=.o)
OBJ2= $(SRC2:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
		$(CC) $(OBJ) -o $(NAME_DEBUG)
		./$(NAME_DEBUG)

dyna:$(OBJ2)
		$(CC) $(OBJ2) -o $(NAME_DEBUG)
		./$(NAME_DEBUG)

%.o:%.c
		$(CC) $(FLAGS) $< -o $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)
		rm -rf $(NAME_DEBUG)

re: fclean all

.PHONY: clean fclean re test_unitaire
