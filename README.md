TD1/exo1.txt                                                                                        0000600 0145371 0116101 00000000574 13046335225 013170  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                1) ( C'est un type qui n'est pas un type de donné du langage C ) FAUX

   C'est un type générique indépendant de l'implémentation.

2) Les structures employés et le choix de complexité en temps et en espace.

3) Pour fixer la sementique générale : 
   - réemployer dans plusieurs programmes.
   - Pour un algo donné, on peut remplacer l'implémentation par un autre.
 
                                                                                                                                    TD1/Makefile                                                                                        0000600 0145371 0116101 00000000775 13050604720 013210  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                NAME=TAD1
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
   TD1/part1.txt                                                                                       0000600 0145371 0116101 00000002760 13046335225 013342  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                **Exercice 2** : (is empty)

1)
	int set__is_empty(struct set* set);

2)
	L'espace mémoire utilisé est moindre lors d'un passage par adresse. (surtout pour un ensemble de grande cardinalité.)

3)
	Car c'est une structure set qui est placé en paramètre.

**Exercice 3** : (add)

1)
	Grace au paramètrage par adresse, c'est la zone mémoire sur laquelle est l'ensemble qui est directement modifié.

2)
	Le retour d'une valeur représentant la réussite ou l'échec de l'opération peut être utile, par exemple pour savoir si :
	- l'element était déjà dans l'ensemble
	- la structure est pleine.
	- l'entier est négatif

3)
	int set__add(struct set* set, int val);

**Execrice 4** : (construct set)
1)
	 a)struct set * set__empty();
  
Retourne un pointeur vers une structure : Allocation par le TAD

	 b)struct set set__empty();

Retourne une structure : allocation par le client

	 c)void set__empty(struct set *);
       
Le client place le pointeur en paramètre : Il alloue la place

2)

	Pour savoir quelle place allouer

3)  a) Sert à laisser le TAD alouer la place, on travaille avec le pointeur retourné.
       + : évite de copier les données 
       - : Nécessite allocation dynamique

    b) +: 
       -: plusieurs allocations : copies

    c) Il faut allouer la place à l'avance et donner le pointeur vers la lace allouée.
       + : évite de copier les données et gère la place
       - : Il faut bien prévoir la place à allouer à l'avance


**Exercice 5**
	   implémentation faite
                TD1/part2.txt                                                                                       0000600 0145371 0116101 00000000143 13046335225 013334  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                **Exercice 6**
3- Pour pouvoir rajouter des champs à la structure tel que la taille de l'élement
                                                                                                                                                                                                                                                                                                                                                                                                                             TD1/set.h                                                                                           0000600 0145371 0116101 00000000666 13050601063 012510  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #ifndef SET_H
# define SET_H

#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define ERROR -1

void	set__empty(struct set *);
int	set__is_empty(struct set const *);
int	set__find(struct set const*, int val);
int	set__shift_right(struct set *a, int i, int j);
int	set__shift_left(struct set *a, int i, int j);
int	set__size(struct set const*);
int	set__add(struct set *, int val);
int	set__remove(struct set *, int val);

#endif
                                                                          TD1/set_sentinel.c                                                                                  0000600 0145371 0116101 00000004463 13050601063 014403  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include "set_sentinel.h"
#include <stdio.h>

#define SUCCESS 1
#define FAILURE 0
#define ERROR -1


void	set__empty(struct set *a)
{	
        if(a == NULL)
	        return ;
  	(a->s)[0] = -1;
  	(a->s)[SET_SIZE - 1] = -2;
	return ;
}

int	set__is_empty(struct set const *a)
{
	if (a == NULL)
		return (ERROR);
	if ((a->s)[0] == -1)
		return (SUCCESS);
	return (FAILURE);
}

int        set__find(struct set const *a, int val)
{
    int    begin;
    int    end;
    int    mid;
    int    size;

        size = set__size(a);
        if (size == 0 || a == NULL || val < 0)
            return (0);
        begin = 0;
        end = size - 1;
        while ((end - begin) > 1)
        {
            mid = (end + begin) / 2;
            if ((a->s)[mid] == val)
                return (mid);
            else if ((a->s)[mid] > val)
                end = mid;
            else
                begin = mid;
        }
	
        if (val > (a->s)[begin])
	{
	  return (begin + 1);
	}
	else
	{
	    return (begin);
	 }
}

int	set__shift_right(struct set *a, int i, int j) //i first index to move right and j last index to move right
{
	if (j + 2 > SET_SIZE || (a->s)[j + 2] == -2)
		return (FAILURE);
	(a->s)[j + 2] = -1;
	for(int k = j; k >= i; k--)
		(a->s)[k + 1] = (a->s)[k];				
	return (SUCCESS);
}

int	set__shift_left(struct set *a, int i, int j) //i first index to move left and j last index to move right (if i = 0, the value is lost, else, the value i-1 is lost)
{
        
        if( a == NULL || i < 0 || j < 0 || j > SET_SIZE - 1)
	         return (ERROR);
	else if ((a->s)[0] == -1 || i == 0)
	         return (FAILURE);
	for(int k = i; k <= j; k++)
	  {
		(a->s)[k - 1] = (a->s)[k];
	}

	if (j == SET_SIZE - 1)
	        (a->s)[j] = -2;
	else
	        (a->s)[j] = -1;
	return (SUCCESS);
}
	
int	set__size(struct set const *a)
{
	int	j;
	
	for (j = 0; j <= SET_SIZE; j++)
	{
		if ((a->s)[j] <= -1)
			return (j);	
	}
	return (ERROR);
}
	
int	set__add(struct set *a, int val)
{
	int	i;
	int     size;

	i = set__find(a, val);
	if(val == (a->s)[i])
	  return(FAILURE);
	size = set__size(a);
	set__shift_right(a, i, size - 1);
	(a->s)[i] = val;
	return (SUCCESS);
	
}

int	set__remove(struct set *a, int val)
{
        int	j;

	j = set__find(a, val);
	if(val != (a->s)[j])
	  return(FAILURE);
	set__shift_left(a, j+1, SET_SIZE - 1);
	return (SUCCESS);
}
                                                                                                                                                                                                             TD1/set_sentinel_d.c                                                                                0000600 0145371 0116101 00000004517 13050604720 014711  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include "set_sentinel_d.h"


void	set__empty(struct set *a)
{
		if (a == NULL)
			return ;
		a->size = 0;
		if (a->s != NULL)
			free(a->s);
		a->s = NULL;
		a->capacity = 0;
		return ;
}

int		set__is_empty(struct set const *a)
{
		if (a == NULL)
			return (0);
		else if (a->size == 0)
			return (1);
		else
			return (0);
}


int		set__size(struct set const *a)
{
	if (a == NULL)
		return (0);
	return (a->size);
}

int		find(struct set const *a, int val)
{
	int	debut;
	int	fin;
	int	mid;
	int	size;

		size = set__size(a);
		if (size == 0 || a == NULL || val < 0)
			return (0);
		debut = 0;
		fin = size - 1;
		while ((fin - debut) > 1)
		{
			mid = (fin + debut) / 2;
			if ((a->s)[mid] == val)
				return (mid);
			else if ((a->s)[mid] > val)
				fin = mid;
			else
				debut = mid;
		}
		if (val > (a->s)[debut])
			return (debut + 1);
		else
			return (debut);
}


int					shift_right(struct set *a, unsigned int i, unsigned int j)
{
	size_t			capacity;
	unsigned int	pos;

	pos = j + 1;
	capacity = (a->capacity);
	if (a == NULL || a->s == NULL || (j - i) > capacity || j > capacity || i > capacity || j + 1 > capacity)
		return (0);
	while (pos > i)
	{
		(a->s)[pos] = (a->s)[pos - 1];
		pos--;
	}
	return (1);
}


int					shift_left(struct set *a, unsigned int i, unsigned int j)
{
	size_t			capacity;
	unsigned int	pos;

	pos = i - 1;
	capacity = (a->capacity);
	if (a == NULL || a->s == NULL || (j - i) > capacity  || i ==  0)
		return (0);
	while (pos < j)
	{
		(a->s)[pos] = (a->s)[pos + 1];
		pos++;
	}
	return (1);
}

int		set__add(struct set *a, int val)
{
	unsigned int		pos;

	if (a == NULL)
		return (0);
	pos = find(a, val);
	if ((a->capacity) > pos && (a->s)[pos] == val)
		return (1);
	if (a->size == a->capacity)
	{
		if (a->capacity == 0)
			a->capacity += 1;
		else
			a->capacity *= 2;
		(a->s) = (int *)realloc(a->s, a->capacity);
		if (a == NULL)
			return (0);
	}
	shift_right(a, pos, a->size - 1);
	(a->s)[pos] = val;
	(a->size) += 1;
	return (1);
}

int		set__remove(struct set *a, int val)
{
	unsigned int		pos;

	if (a == NULL)
		return (0);
	pos = find(a, val);
	if (a->size == 0 || ((a->capacity) > pos && (a->s)[pos] != val))
		return (1);
	shift_left(a, pos + 1, a->size - 1);
	(a->size) -= 1;
	if (a->size - 1 == a->capacity / 2)
		a->capacity /= 2;
	(a->s) = (int *)realloc(a->s, a->capacity);
	if (a == NULL)
		return (0);
	return (1);
}
                                                                                                                                                                                 TD1/set_sentinel_d.h                                                                                0000600 0145371 0116101 00000000234 13050604720 014706  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #ifndef SET_SENTINEL_D_H
# define SET_SENTINEL_D_H

#include <stdlib.h>

struct set
{
	int	*s;
	size_t	capacity;
	size_t	size;	
};

#include "set.h"
#endif
                                                                                                                                                                                                                                                                                                                                                                    TD1/set_sentinel.h                                                                                  0000600 0145371 0116101 00000000201 13050601063 014372  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #ifndef SET_SENTINEL_H
# define SET_SENTINEL_H
# define SET_SIZE 10

struct	set
{
	int	s[SET_SIZE];
};

# include "set.h"
#endif
                                                                                                                                                                                                                                                                                                                                                                                               TD1/test_unitaire2.c                                                                                0000600 0145371 0116101 00000007222 13050604720 014647  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include "set_sentinel_d.h"
#include <assert.h>
#include <stdio.h>

void	test_find()
{
	printf("------------Test find---------------\n");
	printf("Test Pointeur NULL\n");
	assert(!find(NULL, 10));

	printf("Test TAD empty\n");
	struct set s1;
	set__empty(&s1);
	assert(!find(&s1, 10));

	s1.s = (int *)malloc(sizeof(int) * 3);
	if (s1.s == NULL)
		return ;
	s1.capacity = 3;
	s1.size = 3;
	s1.s[0] = 2;
	s1.s[1] = 4;
	s1.s[2] = 5;
	printf("Test element existant\n");
	assert(find(&s1,  2) == 0);
	printf("Test element non existant\n");
	assert(find(&s1,  3) == 1);
}


void	test__shift_right()
{
	printf("-----------Test shift_right-----------\n");

	struct	set s1;
	set__empty(&s1);
	printf("TEST Decalage 2 elements\n");
	s1.s = (int *)malloc(sizeof(int) * 4);
	if (s1.s == NULL)
		return ;
	s1.capacity = 4;
	s1.size = 3;
	s1.s[0] = 1;
	s1.s[1] = 2;
	s1.s[2] = 3;
	shift_right(&s1, 0, 2); 
	assert((s1.s[1] == 1) && (s1.s[2] == 2) && (s1.s[3] == 3));

}

void	test__shift_left()
{
	printf("-----------Test shift_left-----------\n");

	struct	set s1;
	set__empty(&s1);
	printf("TEST Decalage non autorisee\n");
	s1.s = (int *)malloc(sizeof(int) * 4);
	if (s1.s == NULL)
		return ;
	s1.capacity = 4;
	s1.size = 3;
	s1.s[0] = 1;
	s1.s[1] = 2;
	s1.s[2] = 3;
	assert(!shift_left(&s1, 0, 2));
	printf("TEST Decalage\n");
	assert(shift_left(&s1, 1, 2));
	assert((s1.s[0] == 2) && (s1.s[1] == 3) && (s1.s[2] == 3));
	printf("TEST Decalage 1 element\n");
	assert(shift_left(&s1, 1, 1));
	assert(s1.s[0] == 3);
}




void	test__set__is_empty()
{
	printf("------------Test set__is_empty-------------\n");
	
	printf("Test ENSEMBLE VIDE\n");
	struct	set s1;
	set__empty(&s1);
	assert(set__is_empty(&s1));

	printf("Test ENSEMBLE NON VIDE\n");
	s1.s = (int *)malloc(sizeof(int) * 3);
	if (s1.s == NULL)
		return ;
	s1.capacity = 3;
	s1.size = 3;
	s1.s[0] = 2;
	s1.s[1] = 4;
	s1.s[2] = 5;
	assert(!set__is_empty(&s1));
	
	printf("Test Pointeur NULL\n");
	set__empty(NULL);	
	printf("Ok\n");
}

void	test__set__size()
{
	printf("------------------Test set__size--------------\n");
	
	printf("TEST ENSEMBLE VIDE\n");
	struct	set s1;
	set__empty(&s1);
	assert((set__size(&s1) == 0));

	printf("Test ENSEMBLE NON VIDE\n");
	s1.s = (int *)malloc(sizeof(int) * 3);
	if (s1.s == NULL)
		return ;
	s1.capacity = 3;
	s1.size = 3;
	s1.s[0] = 2;
	s1.s[1] = 4;
	s1.s[2] = 5;
	assert((set__size(&s1) == 3));
	
	printf("Ok\n");
}


void	test__set__add()
{
	printf("-------Test set__add--------\n");
	
	printf("TEST ENSEMBLE VIDE\n");
	struct	set s1;
	set__empty(&s1);
	set__add(&s1, 1);
	assert((set__size(&s1) == 1) && (s1.s)[0] == 1);
	printf("TEST element deja existant\n");
	set__add(&s1, 1);
	assert((set__size(&s1) == 1));
	printf("TEST element double capacity\n");
	set__add(&s1, 2);
	assert((set__size(&s1) == 2));
	printf("Ok\n");
}


/*
void	test__set__find()
{
	printf("Test set__find\n");
	
	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert((set__find(&s1, 7) == -1));

	//Test ENSEMBLE NON VIDE
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);
	assert(set__find(&s2, 7) == 1);
	assert(set__find(&s2, 1) == 0);

	printf("Ok\n");
}
*/
void	test__set__remove()
{
	int		i;

	i = 0;
	printf("--------------Test set__remove------------\n");
	
	printf("TEST ENSEMBLE VIDE\n");
	struct	set s1;
	set__empty(&s1);
	assert((set__remove(&s1, 1) == 1));

	printf("Test ENSEMBLE NON VIDE\n");
	set__add(&s1, 1);
	set__add(&s1, 7);
	assert((set__remove(&s1, 1) == 1));
	assert(s1.s[0] == 7 && s1.size == 1);
	printf("Ok\n");
}

int	main()
{
	test__set__is_empty();
	test__set__size();
	test__set__add();
	//test__set__find();	
	test__set__remove();
	test_find();
	test__shift_right();
	test__shift_left();
	return (0);
}
                                                                                                                                                                                                                                                                                                                                                                              TD1/test_unitaire.c                                                                                 0000600 0145371 0116101 00000006116 13050601063 014563  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include "set_sentinel.h"
#include <assert.h>
#include <stdio.h>

void	test__set__is_empty()
{
	printf("Test set__is_empty\n");

	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert(set__is_empty(&s1));

	//Test ENSEMBLE NON VIDE
	struct	set s2;

	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);
	assert(!(set__is_empty(&s2)));
	
	printf("Ok\n");
}

void	test__shift_right()
{
	printf("Test shift_right\n");

	//TEST DECALAGE HORS TAILLE MAX
	struct	set s1;
	set__empty(&s1);
	assert(set__shift_right(&s1, 0, SET_SIZE - 1) == FAILURE);

	//TEST DECALAGE LEGAL
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 10);
	set__add(&s2, 15);	
	set__shift_right(&s2, 0, 2);
	assert(s2.s[1] == 10 && s2.s[2] == 15 && s2.s[SET_SIZE - 1] == -2 && s2.s[3] == -1);
	
	//AUTRE DECALAGE
	struct set s3;
	set__empty(&s3);
	set__add(&s3, 2);
	set__add(&s3, 15);
	set__add(&s3, 10);
	set__add(&s3, 7);
	set__shift_right(&s3, 0, 3);
	assert(s3.s[1] == 2 && s3.s[2] == 7 && s3.s[3] == 10 && s3.s[4] == 15 && s3.s[5] == -1 && s3.s[SET_SIZE - 1] == -2);
	
	printf("OK\n");
}

void	test__shift_left()
{
	printf("Test shift_left\n");

	//TEST DECALAGE HORS TAILLE MAX
	struct	set s1;
	set__empty(&s1);
	assert(set__shift_left(&s1, 0, SET_SIZE - 1) == FAILURE);

	//TEST DECALAGE LEGAL
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 10);
	set__add(&s2, 15);
	set__add(&s2, 2);
	assert (set__shift_left(&s2, 0, 1) == FAILURE );
	set__shift_left(&s2, 1, 3);
	assert(s2.s[0] == 10 && s2.s[SET_SIZE - 1] == -2 && s2.s[1] == 15 && s2.s[2] == -1);

	printf("OK\n");
}

void	test__set__size()
{
	printf("Test set__size\n");
	
	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert((set__size(&s1) == 0));

	//Test ENSEMBLE NON VIDE
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);

	set__add(&s2, 1);
	assert((set__size(&s2) == 2));
	
	printf("Ok\n");
}

void	test__set__add()
{
	printf("Test set__add\n");
	
	//TEST ENSEMBLE VIDE

	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	assert((set__size(&s2) == 1) && s2.s[0] == 1 && s2.s[1] == -1 && s2.s[SET_SIZE - 1] == -2);
	set__add(&s2, 1);
	assert((set__size(&s2) == 1) && s2.s[0] == 1 && s2.s[1] == -1 && s2.s[SET_SIZE - 1] == -2);
	printf("Ok\n");
}

void	test__set__find()
{
	printf("Test set__find\n");
	
	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert((set__find(&s1, 7) == FAILURE));

	//Test ENSEMBLE NON VIDE
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);
	assert(set__find(&s2, 7) == 1);
	assert(set__find(&s2, 1) == 0);
	assert(set__find(&s2, 2) == 1);

	printf("Ok\n");
}

void	test__set__remove()
{
	printf("Test set__remove\n");
	
	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert((set__remove(&s1, 1) == FAILURE));

	//Test ENSEMBLE NON VIDE
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);
	assert((set__remove(&s2, 1) == 1));
	
	assert( (s2.s)[0] == 7);
	assert( (s2.s)[1] == -1);
		
	printf("Ok\n");
}

int	main()
{
	test__set__is_empty();
	test__shift_right();
	test__shift_left();
	test__set__size();
	test__set__find();
	test__set__add();
	test__set__remove();
	return (0);
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                  TD2/link.c                                                                                          0000600 0145371 0116101 00000005135 13050575322 012652  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include "link.h"
#include "unistd.h"

void				lnk__empty(struct link *a)
{
	struct lelement *sentinel;
	
	if (a == NULL)
		return ;
	sentinel = (struct lelement *)malloc(sizeof(struct lelement));
	if (sentinel == NULL)
		return ;
	sentinel->data = -1;
	sentinel->next = sentinel;
	a->head = sentinel;
}

struct lelement		*lnk__first(struct link *a)
{
	if (a == NULL || a->head == NULL)
		return (NULL);
	return (a->head);
}


int			llm__is_end_mark(struct lelement *is_sentinel)
{
	if (is_sentinel == NULL)
		return (0);
	return (is_sentinel->next == is_sentinel);
}

void			lnk__add_head(struct link *a, struct lelement *new)
{
	if (a == NULL || a->head == NULL || new == NULL)
		return ;
	new->next = a->head;
	a->head = new;
	return ;
}

struct lelement		*lnk__remove_head(struct link *a)
{
	struct lelement	*next;
	struct lelement	*del;

	if (a == NULL || a->head == NULL || llm__is_end_mark(a->head))
		return (NULL);
	del = a->head;
	next = a->head->next;
	a->head = next;
	return (del);
}

struct lelement		*llm__next(struct lelement *a)
{
	if (a == NULL || llm__is_end_mark(a->next))
		return (a);
	else
		return (a->next);
}

struct lelement		*lnk__add_after(struct link *lst, struct lelement *begin, struct lelement *new)
{
	struct lelement *tmp;

	if (lst == NULL || lst->head == NULL || begin == NULL || new == NULL || llm__is_end_mark(begin))
		return (NULL);
	tmp = begin->next;
	begin->next = new;
	new->next = tmp;
	return (new);
}

struct lelement		*lnk__remove_after(struct link *lst, struct lelement *begin)
{
	struct lelement *del;
	struct lelement *next;

	if (lst == NULL || lst->head == NULL || begin == NULL || llm__is_end_mark(begin))
		return (NULL);
	del = begin->next;
	next = del->next;
	begin->next = next;
	return (del);
}

void			lnk__add_tail(struct link *lst, struct lelement *new)
{
	struct lelement *sentinel;
	struct lelement *tmp;

	if (lst == NULL || lst->head == NULL || new == NULL)
		return ;
	tmp = lst->head;
	if (llm__is_end_mark(tmp))
	{
		lst->head = new;
		new->next = tmp;
		return ;
	}
	while (!llm__is_end_mark(tmp->next))
	{
		tmp = tmp->next;
	}
	sentinel = tmp->next;
	tmp->next = new;
	new->next = sentinel;
}

struct lelement			*lnk__remove_tail(struct link *lst)
{
	struct lelement *del;
	struct lelement *sentinel;
	struct lelement *tmp;

	if (lst == NULL || lst->head == NULL || llm__is_end_mark(lst->head))
		return (NULL);
	tmp = lst->head;
	if (llm__is_end_mark(tmp->next))
	{
		del = tmp;
		lst->head = tmp->next;
		return (del);
	}
	while (!llm__is_end_mark(tmp->next->next))
	{
		tmp = tmp->next;
	}
	del = tmp->next;
	sentinel = tmp->next->next;
	tmp->next = sentinel;
	return (del);
}
                                                                                                                                                                                                                                                                                                                                                                                                                                   TD2/link.h                                                                                          0000600 0145371 0116101 00000001403 13050575322 012651  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #ifndef LINK_H
#define LINK_H
#include <stdlib.h>
#include <stdio.h>

struct 			lelement
{
	int		data;
	struct lelement	*next;
};

struct			link
{
	struct lelement *head;
};

void			lnk__empty(struct link *a);
struct lelement		*lnk__first(struct link *a);
int			llm__is_end_mark(struct lelement *is_sentinel);
void			lnk__add_head(struct link *a, struct lelement *new);
struct lelement		*lnk__remove_head(struct link *a);
struct lelement		*llm__next(struct lelement *a);
struct lelement		*lnk__add_after(struct link *lst, struct lelement *begin, struct lelement *new);
struct lelement		*lnk__remove_after(struct link *lst, struct lelement *begin);
void			lnk__add_tail(struct link *lst, struct lelement *new);
struct lelement		*lnk__remove_tail(struct link *lst);
#endif
                                                                                                                                                                                                                                                             TD2/Makefile                                                                                        0000600 0145371 0116101 00000001064 13050575322 013206  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                NAME_DEBUG=test_unitaire
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
                                                                                                                                                                                                                                                                                                                                                                                                                                                                            TD2/set_link.c                                                                                      0000600 0145371 0116101 00000003326 13050575322 013525  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include "set_link.h"

void	set__empty(struct set *s)
{
	struct	link	*l;

	l = (struct link *)malloc(sizeof(struct link));
	s->l = l;
	lnk__empty(s->l);
	return ;
}

int	set__is_empty(struct set const *s)
{
	if (s == NULL || s->l == NULL || s->l->head == NULL)
		return (0);
	return ((llm__is_end_mark(s->l->head)));
}

int	set__find(struct set const* s, int val)
{
	struct lelement *tmp;

	if (s == NULL || s->l == NULL || s->l->head == NULL)
		return (0);
	tmp = lnk__first(s->l);
	while (!llm__is_end_mark(tmp))
	{
		if (tmp->data == val)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	set__size(struct set const *s)
{
	struct lelement *tmp;
	int		i;

	i = 0;
	if (s == NULL || s->l == NULL || s->l->head == NULL)
		return (i);
	tmp = lnk__first(s->l);
	while (!llm__is_end_mark(tmp))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}



int	set__add(struct set *s, int val)
{
	struct lelement *new;
	struct lelement *tmp;

	if (s == NULL || s->l == NULL || set__find(s, val))
		return (0);
	new = (struct lelement *)malloc(sizeof(struct lelement));
	new->data = val;
	if (new == NULL)
		return (0);
	tmp = lnk__first(s->l);
	if (llm__is_end_mark(tmp))
	{
		lnk__add_head(s->l, new);
		return (1);
	}
	while (!llm__is_end_mark(tmp->next) && !(tmp->next->data >= val))
	{
		tmp = tmp->next;
	}
	lnk__add_after(s->l, tmp, new);
	return (1);
	

}

int	set__remove(struct set *s, int val)
{
	struct lelement *del;
	struct lelement *tmp;

	if (s == NULL || s->l == NULL)
		return (0);
	tmp = lnk__first(s->l);
	if (llm__is_end_mark(tmp))
		return (0);
	while (!llm__is_end_mark(tmp->next) && !(tmp->next->data >= val))
	{
		tmp = tmp->next;
	}
	if (tmp->data != val)
		return (0);
	del = lnk__remove_after(s->l, tmp);
	free(del);
	return (1);
}
                                                                                                                                                                                                                                                                                                          TD2/set_link.h                                                                                      0000600 0145371 0116101 00000000540 13050575322 013525  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #ifndef SET_LINK_H
# define SET_LINK_H
#include "link.h"

struct set
{
	struct link	*l;
};
#include "../set.h"


void	set__empty(struct set *s);
int	set__is_empty(struct set const *s);
int	set__find(struct set const* s, int val);
int	set__size(struct set const *s);
int	set__add(struct set *s, int val);
int	set__remove(struct set *s, int val);
#endif
                                                                                                                                                                TD2/test_unitaire.c                                                                                 0000600 0145371 0116101 00000007156 13050575322 014601  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include <assert.h>
#include <stdio.h>
#include "link.h"

void	test_lnk__empty()
{

	struct	link l;
	
	printf("---------------------test de lnk__empty--------------\n");
  	l.head = NULL;
	lnk__empty(&l);
 	assert(l.head->next == l.head);
	free(l.head);
	printf("OK\n");
}

void	test_lnk__first()
{
  	struct link l;
  
	printf("----------------test de lnk__first----------------\n");
	lnk__empty(&l);
  	assert(lnk__first(&l) == (l.head));
	free(l.head);
	printf("OK\n");
}

void test_llm__is_end_mark()
{

  	struct lelement e;
	struct lelement next;
  
	printf("------------------test de lmm__is_end_mark--------------");	
  	printf("\nEntree pointeur NULL\n");
	assert(llm__is_end_mark(NULL) == 0);
 	e.next = &e;
  	printf("Entree sentinelle\n");
	assert(llm__is_end_mark(&e) == 1);
	e.next = &next;
  	printf("Entree non sentinelle\n");
	assert(llm__is_end_mark(&e) == 0);
	printf("OK\n");
}

void	test_lnk__add_head()
{
	struct link l;
	struct lelement new;

	printf("-------test de lnk__add_head----------\n");
	
	printf("Liste vide\n");
	lnk__empty(&l);
	new.data = 42;
	lnk__add_head(&l, &new);
	assert(l.head->data == 42);
	free(l.head->next);
	printf("OK\n");
}

void	test_lnk__remove_head()
{
  	struct link l;
  	struct lelement e;
  
  	printf("------------test de lnk__remove_head---------------\n");
	lnk__empty(&l);
  	printf("Liste vide\n");
  	assert(lnk__remove_head(&l) == NULL);
  	printf("Liste a un element\n");
	lnk__add_head(&l, &e);
  	assert(lnk__remove_head(&l) == &e);
  	assert(llm__is_end_mark(l.head));
	free(l.head);
	printf("OK\n");
}

void	test_llm__next()
{
	struct lelement e1;
	struct lelement e2;
  	struct link l; 
	
	printf("-------------test de llm__next-----------\n");
	lnk__empty(&l);
  	lnk__add_head(&l, &e1);
  	lnk__add_head(&l, &e2);
  	assert(llm__next(&e2) == &e1);
  	free((l.head)->next->next);
	printf("OK\n");
}

void	test_lnk__add_after()
{
	struct link l;
  	struct lelement e1;
  	struct lelement e2;
  	struct lelement e3;
  
	printf("----------------test de lnk__add_after-------------------\n");
	lnk__empty(&l);
  	lnk__add_head(&l, &e2);
  	lnk__add_head(&l, &e1);
  	lnk__add_after(&l, &e1, &e3);    
	assert(e1.next == &e3);
	assert(e3.next == &e2);
	assert(llm__is_end_mark(e2.next));
	free(e2.next);
	printf("OK\n");
}

void	test_lnk__remove_after()
{
	struct link l;
	struct lelement e1;
	struct lelement e2;
	struct lelement e3;
  
	printf("--------------test de lnk__remove_after-----------------\n");
	lnk__empty(&l);
	lnk__add_head(&l, &e3);
	lnk__add_head(&l, &e2);
	lnk__add_head(&l, &e1);
	assert(lnk__remove_after(&l, &e1) == &e2);    
	assert(e1.next == &e3);
	assert(llm__is_end_mark(e3.next));
	free(e3.next);
	printf("OK\n");
}

void test_lnk__add_tail()
{
	struct link l;
	struct lelement e1;
	struct lelement e2;
  
	
	printf("--------------test de lnk__add_tail-----------------\n");
	lnk__empty(&l);
	lnk__add_tail(&l, &e1);
	lnk__add_tail(&l, &e2);    
	assert(e1.next == &e2);
	assert(llm__is_end_mark(e2.next));
	free(e2.next);
	printf("OK\n");
}

void test_lnk__remove_tail()
{
	struct link l;
	struct lelement e1;
	struct lelement e2;
	struct lelement e3;
  
	printf("---------------test de lnk__remove_tail-----------------\n");
	lnk__empty(&l);
	lnk__add_tail(&l, &e1);
  	lnk__add_tail(&l, &e2);    
  	lnk__add_tail(&l, &e3); 
	assert(lnk__remove_tail(&l) == &e3);
	assert(llm__is_end_mark(e2.next));
	free(e2.next);
	printf("OK\n");
}

int main()
{

  test_lnk__empty();
  test_lnk__first();
  test_llm__is_end_mark();
  test_lnk__add_head();
  test_lnk__remove_head();
  test_llm__next();
  test_lnk__add_after();
  test_lnk__remove_after();
  test_lnk__add_tail();
  test_lnk__remove_tail();

}
                                                                                                                                                                                                                                                                                                                                                                                                                  TD2/#test_unitaires.c#                                                                              0000600 0145371 0116101 00000005516 13047334307 015072  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include <assert.h>
#include <stdio.h>

#include "link.c"

void test_lnk__empty(){

  printf("test de lnk__empty ...");

  struct link *l;
  lnk__empty(l);
  assert(l->head->next == l->head);

  printf("OK\n");
}

void test_lnk__first(){

  printf("test de lnk__first ...");

  struct link *l;
  lnk__empty(l);
  //assert(lnk_first(l) == (l->head));

  printf("OK\n");
}

void test_llm__is_end_mark(){
  
  printf("test de lmm__is_end_mark ...");

  struct lelement *e;
  assert(llm__is_end_mark(NULL) == 0);
  e->next = e;
  assert(llm__is_end_mark(e) == 1);
  e->next = e+1;
  assert(llm__is_end_mark(e) == 0);

  printf("OK\n");
}

void test_lnk__add_head(){
  
  printf("test de lnk__add_head...");

  struct link *l;
  struct lelement *new;

  lnk__add_head(l,new);

  assert(l->head == new);

  printf("OK\n");
}

void test_lnk__remove_head(){
  printf("test de lnk__remove_head");

  struct link *l;
  struct lelement *e;
  lnk__empty(l);
  lnk__add_head(l,e);
  assert(lnk__remove_head() == e);
  assert(llm__is_end_mark(l->head));

  printf("OK\n");

}

void test_llm__next(){
  printf("test de llm__next");
  
  struct lelement *e1;
  struct lelement *e2;
  struct link *l;
  lnk__empty(l);
  lnk__add_head(l,e1);
  lnk__add_head(l,e2);
  assert(llm__next(e1) == e2);

  printf("OK\n");

}

void test_lnk__add_after(){
  printf("test de lnk__add_after");

  struct link *l;
  struct lelement *e1;
  struct lelement *e2;
  struct lelement *e3;
  lnk__empty(l);
  lnk__add_head(l,e2);
  lnk__add_head(l,e1);
  lnk__add_after(l,e1,e3);    
  assert(e1->next == e3);
  assert(e3->next == e2);
  assert(llm__is_end_mark(e2));

  printf("OK\n");
}

void test_lnk__remove_after(){
  printf("test de lnk__remove_after");

  struct link *l;
  struct lelement *e1;
  struct lelement *e2;
  struct lelement *e3;
  lnk__empty(l);
  lnk__add_head(l,e3);
  lnk__add_head(l,e2);
  lnk__add_head(l,e1);
  assert (lnk__remove_after(l,e1) == e2 );    
  assert(e1->next == e3);
  assert(llm__is_end_mark(e3));

  printf("OK\n");
}

void test_lnk__add_tail(){
  printf("test de lnk__add_tail");
  
  struct link *l;
  struct lelement *e1;
  struct lelement *e2;
  lnk__empty(l);
  lnk__add_tail(l,e1);
  lnk__add_tail(l,e2);    
  assert(e1->next == e2);
  assert(llm__is_end_mark(e2));
}

void test_lnk__remove_tail(){
  printf("test de lnk__remove_tail");
  
  struct link *l;
  struct lelement *e1;
  struct lelement *e2;
  struct lelement *e3;
  lnk__empty(l);
  lnk__add_tail(l,e1);
  lnk__add_tail(l,e2);    
  lnk__add_tail(l,e3);    
  assert(lnk__remove_tail(l) == e3;);
  assert(e1->next == e2);
  assert(llm__is_end_mark(e2));
}

int main(){

  test_lnk__empty();
  //test_lnk__first();
  test_llm__is_end_mark();
  test_lnk__add_head();
  test_lnk__remove_head();
  test_llm__next();
  test_lnk__add_after();
  test_lnk__remove_after();
  test_lnk__add_tail();
  test_lnk__remove_tail();

}
                                                                                                                                                                                  TD2/test_unitaires.c                                                                                0000600 0145371 0116101 00000005515 13047333760 014765  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include <assert.h>
#include <stdio.h>

#include "link.c"

void test_lnk__empty(){

  printf("test de lnk__empty ...");

  struct link *l;
  lnk__empty(l);
  assert(l->head->next == l->head);

  printf("OK\n");
}

void test_lnk__first(){

  printf("test de lnk__first ...");

  struct link *l;
  lnk__empty(l);
  //assert(lnk_first(l) == (l->head));

  printf("OK\n");
}

void test_llm__is_end_mark(){
  
  printf("test de lmm__is_end_mark ...");

  struct element *e;
  assert(llm__is_end_mark(NULL) == 0);
  e->next = e;
  assert(llm__is_end_mark(e) == 1);
  e->next = e+1;
  assert(llm__is_end_mark(e) == 0);

  printf("OK\n");
}

void test_lnk__add_head(){
  
  printf("test de lnk__add_head...");

  struct link *l;
  struct lelement *new;

  lnk__add_head(l,new);

  assert(l->head == new);

  printf("OK\n");
}

void test_lnk__remove_head(){
  printf("test de lnk__remove_head");

  struct link *l;
  struct lelement *e;
  lnk__empty(l);
  lnk__add_head(l,e);
  assert(lnk__remove_head() == e);
  assert(llm__is_end_mark(l->head));

  printf("OK\n");

}

void test_llm__next(){
  printf("test de llm__next");
  
  struct lelement *e1;
  struct lelement *e2;
  struct link *l;
  lnk__empty(l);
  lnk__add_head(l,e1);
  lnk__add_head(l,e2);
  assert(llm__next(e1) == e2);

  printf("OK\n");

}

void test_lnk__add_after(){
  printf("test de lnk__add_after");

  struct link *l;
  struct lelement *e1;
  struct lelement *e2;
  struct lelement *e3;
  lnk__empty(l);
  lnk__add_head(l,e2);
  lnk__add_head(l,e1);
  lnk__add_after(l,e1,e3);    
  assert(e1->next == e3);
  assert(e3->next == e2);
  assert(llm__is_end_mark(e2));

  printf("OK\n");
}

void test_lnk__remove_after(){
  printf("test de lnk__remove_after");

  struct link *l;
  struct lelement *e1;
  struct lelement *e2;
  struct lelement *e3;
  lnk__empty(l);
  lnk__add_head(l,e3);
  lnk__add_head(l,e2);
  lnk__add_head(l,e1);
  assert (lnk__remove_after(l,e1) == e2 );    
  assert(e1->next == e3);
  assert(llm__is_end_mark(e3));

  printf("OK\n");
}

void test_lnk__add_tail(){
  printf("test de lnk__add_tail");
  
  struct link *l;
  struct lelement *e1;
  struct lelement *e2;
  lnk__empty(l);
  lnk__add_tail(l,e1);
  lnk__add_tail(l,e2);    
  assert(e1->next == e2);
  assert(llm__is_end_mark(e2));
}

void test_lnk__remove_tail(){
  printf("test de lnk__remove_tail");
  
  struct link *l;
  struct lelement *e1;
  struct lelement *e2;
  struct lelement *e3;
  lnk__empty(l);
  lnk__add_tail(l,e1);
  lnk__add_tail(l,e2);    
  lnk__add_tail(l,e3);    
  assert(lnk__remove_tail(l) == e3;);
  assert(e1->next == e2);
  assert(llm__is_end_mark(e2));
}

int main(){

  test_lnk__empty();
  //test_lnk__first();
  test_llm__is_end_mark();
  test_lnk__add_head();
  test_lnk__remove_head();
  test_llm__next();
  test_lnk__add_after();
  test_lnk__remove_after();
  test_lnk__add_tail();
  test_lnk__remove_tail();

}
                                                                                                                                                                                   TD2/test_unitaires.c~                                                                               0000600 0145371 0116101 00000000304 13047324750 015151  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include <link.h>

void test_lnk__empty(){
  struct link l;
  lnk__empty(&l);
  assert(l->head->next == l->head);
}

void test_lnk_first(){
  struct link l;
  lnk__empty(&l);
  
}

int main(){

}
                                                                                                                                                                                                                                                                                                                            TD2/test_unitaire_set.c                                                                             0000600 0145371 0116101 00000003202 13050575322 015440  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include "set_link.h"
#include <assert.h>
#include <stdio.h>

void	test__set__is_empty()
{
	printf("Test set__is_empty\n");

	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert(set__is_empty(&s1));

	//Test ENSEMBLE NON VIDE
	struct	set s2;

	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);
	assert(!(set__is_empty(&s2)));
	
	printf("Ok\n");
}

void	test__set__size()
{
	printf("Test set__size\n");
	
	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert((set__size(&s1) == 0));
	
	//Test ENSEMBLE NON VIDE
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);

	set__add(&s2, 1);
	assert((set__size(&s2) == 2));
	printf("Ok\n");
}

void	test__set__add()
{
	printf("Test set__add\n");
	
	//TEST ENSEMBLE VIDE

	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	assert(set__find(&s2, 1));
	printf("Ok\n");
}

void	test__set__find()
{
	printf("Test set__find\n");
	
	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert((set__find(&s1, 7) == 0));

	//Test ENSEMBLE NON VIDE
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);
	assert(set__find(&s2, 7) == 1);
	assert(set__find(&s2, 1) == 1);
	assert(set__find(&s2, 2) == 0);

	printf("Ok\n");
}

void	test__set__remove()
{
	printf("Test set__remove\n");
	
	//TEST ENSEMBLE VIDE
	struct	set s1;
	set__empty(&s1);
	assert((set__remove(&s1, 1) == 0));

	//Test ENSEMBLE NON VIDE
	struct	set s2;
	set__empty(&s2);
	set__add(&s2, 1);
	set__add(&s2, 7);
	assert((set__remove(&s2, 1) == 1));	
	printf("Ok\n");
}
int	main()
{
	test__set__is_empty();
	test__set__size();
	test__set__find();
	test__set__add();
	test__set__remove();
	return (0);
}
                                                                                                                                                                                                                                                                                                                                                                                              TD3/affectation.c                                                                                   0000600 0145371 0116101 00000001442 13050574637 014206  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                #include <stdio.h>

#if defined SENTINEL
#include "set_sentinel.h"
#elif defined DYNAMIC
#include "set_dynamic.h"
#elif defined LINK
#include "set_link.h"
#else
#error "A set implementation has to be defined"
#endif

int main () {
  printf("creation de s1 avec 5 elements\n");
  struct set s1 = set__empty();

  set__add(&s1, 111);
  set__add(&s1, 222);
  set__add(&s1, 333);
  set__add(&s1, 444);
  set__add(&s1, 555);

  struct set s2 = set__empty();

  printf("affectation : s2 = s1\n");
  s2 = s1;
  printf("s2 nb element:resultat (5) -> %d\n", set__size(&s2));
 
  printf("\najouter 9 dans s1\n");
  set__add(&s1, 9);

  printf("9 dans s2:resultat (NON) -> %s\n", set__find(&s2, 9)? "OK" : "NON");
  printf("s2 nb elements:resultat (5) -> %d\n", set__size(&s2));

  set__free(&s1);
  return 1;
}

                                                                                                                                                                                                                              TD3/set_dynamic-extrait.c                                                                           0000600 0145371 0116101 00000002177 13050574663 015705  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                
struct set{
  int* s;
  size_t capacity;
  size_t size;
  int* cursor;
};

#define MIN_CAPACITY 10 // should be > 0

struct set * set__empty(void) {
  assert( MIN_CAPACITY > 0 );

  struct set * st = malloc(sizeof(struct set));

  st->capacity = MIN_CAPACITY;
  st->s = malloc(st->capacity * sizeof(* st->s));

  st->size = 0;
  return st;
}

int set__add(struct set* st, int data) {
  if (data < 0)
    return SET__ELEMENT_INVALID;

  size_t p = find(st->s, st->size, data);
  if ((p < st->size) && (st->s[p] == data)) // already in
    return SET__ELEMENT_DUPLICATION;

  if (st->size == st->capacity) {
    st->capacity *= 2;
    st->s = realloc(st->s, st->capacity * sizeof(* st->s));
  }

  shift_right(st->s, p, st->size-1);
  st->s[p] = data;
  ++ st->size;

  return SET__NO_ERROR;
}

// with cursor
void set__crs_start(struct set *st) {
  st->cursor = st->s;
}

void set__crs_next(struct set *st) {
  st->cursor++;
}

int  set__crs_has_next(const struct set *st) {
  return st->cursor != (st->s + st->size);
}

int set__crs_data(const struct set *st) {
  return *(st->cursor);
}


                                                                                                                                                                                                                                                                                                                                                                                                 TD3/set_link-extrait.c                                                                              0000600 0145371 0116101 00000002273 13050574656 015215  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                
struct set {
  struct link *link;
};


// returns the position of data in lnk: NULL if data is/should be inserted
// in first position, or a cell p s.t. p->next has value data or is the
// first cell with a value greater than data
static struct lelement * find(struct link *lnk, int data) {
  struct lelement *p = NULL;
  for (struct lelement *l = lnk__first(lnk); 
       !llm__is_end_mark(l); 
       l = llm__next(l)) {
    if (l->data >= data)
      return p;
    p = l;
  }
 return p;
}

int set__add(struct set * st, int data) {
  if (data < 0)
    return SET__ELEMENT_INVALID;

  struct lelement * pred = find(st->link, data);
  struct lelement * current = (pred == NULL ? lnk__first(st->link) : pred->next);
  
  if ( (! llm__is_end_mark(current)) && (current->data == data) ) // already in
    return SET__ELEMENT_DUPLICATION;

  struct lelement * l = malloc(sizeof(struct lelement));
  l->data = data;

  if (pred == NULL)
    lnk__add_head(st->link, l);
  else
    lnk__add_after(st->link, pred, l);

  return SET__NO_ERROR;
}


struct set * set__empty(void) {
  struct set * st = malloc(sizeof(struct set));

  st->link = malloc(sizeof(struct link));
  *(st->link) = lnk__empty();
  return st;
}


                                                                                                                                                                                                                                                                                                                                     TD3/set_sentinel-extrait.c                                                                          0000600 0145371 0116101 00000001703 13050574644 016073  0                                                                                                    ustar   plardin001                      autoipb                                                                                                                                                                                                                
#define SET_SIZE 10

struct set{
  int s[SET_SIZE];
};

#define BORNE    -999

// returns the expected position of c in sorted array s
// the returned value p is such that either s[p]==c,
// or c should be inserted in position p in s
static size_t find(int const s[], int data) {
  size_t i;
  for (i=0; (s[i] != BORNE) && (s[i] < data); ++i );
  return i;
}

int set__add(struct set* st, int data) {
  if (data < 0)
    return SET__ELEMENT_INVALID;

  int i = find(st->s, data);
  if ( (st->s[i] != BORNE) && (st->s[i] == data) ) // already in
    return SET__ELEMENT_DUPLICATION;

  if (st->s[SET_SIZE-1] == BORNE) // out of space
    return SET__CAPACITY_EXCEEDED;
  
  shift_right(st->s, i);
  st->s[i] = data;
  
  return SET__NO_ERROR;
}

#define FREECELL (59)

struct set * set__empty(void) {
  struct set * st = malloc(sizeof(struct set));

  st->s[SET_SIZE-1] = FREECELL;
  st->s[0] = BORNE;
  return st;
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             