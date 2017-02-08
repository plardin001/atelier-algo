NAME_DEBUG=test_unitaire
CC=gcc
FLAGS= -g -std=c99 -c -Wall -Wextra
SRC=link.c
OBJ= $(SRC:.c=.o)
all: $(NAME)

$(NAME):$(OBJ)
		$(CC) $(OBJ) -o $(NAME_DEBUG)
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
