NAME_DEBUG=test_unitaire
NAME_DEBUG_SET=test
CC=gcc
FLAGS= -g -std=c99 -c -Wall -Wextra
SRC=	link.c	\
	test_unitaire.c
SRC2=	link.c	\
	set_link.c	\
	test_unitaire_set.c

OBJ= $(SRC:.c=.o)
OBJ2= $(SRC2:.c=.o)

all: $(NAME_DEBUG)

$(NAME_DEBUG):$(OBJ)
		$(CC) $(OBJ) -o $(NAME_DEBUG)
		./$(NAME_DEBUG)

$(NAME_DEBUG_SET):$(OBJ2)
		$(CC) $(OBJ2) -o $(NAME_DEBUG_SET)
		./$(NAME_DEBUG_SET)

%.o:%.c
		$(CC) $(FLAGS) $< -o $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME_DEBUG)
		rm -rf $(NAME_DEBUG_SET)
re: fclean all

.PHONY: clean fclean re test_unitaire
