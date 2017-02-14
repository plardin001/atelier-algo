#include "set_sentinel.h"
#include <assert.h>
#include <stdio.h>

void	test__set__is_empty()
{
	printf("Test set__is_empty\n");

	//TEST ENSEMBLE VIDE
	struct	set *s1 = set__empty();
	assert(set__is_empty(s1));

	//Test ENSEMBLE NON VIDE
	struct	set *s2 = set__empty();
	set__add(s2, 1);
	set__add(s2, 7);
	assert(!(set__is_empty(s2)));
	
	printf("Ok\n");
}

void	test__shift_right()
{
	printf("Test shift_right\n");

	//TEST DECALAGE HORS TAILLE MAX
	struct	set *s1 = set__empty();
	assert(set__shift_right(s1, 0, SET_SIZE - 1) == FAILURE);

	//TEST DECALAGE LEGAL
	struct	set *s2 = set__empty();
	set__add(s2, 10);
	set__add(s2, 15);	
	set__shift_right(s2, 0, 2);
	assert(s2->s[1] == 10 && s2->s[2] == 15 && s2->s[SET_SIZE - 1] == -2 && s2->s[3] == -1);
	
	//AUTRE DECALAGE
	struct set *s3 = set__empty();
	set__add(s3, 2);
	set__add(s3, 15);
	set__add(s3, 10);
	set__add(s3, 7);
	set__shift_right(s3, 0, 3);
	assert(s3->s[1] == 2 && s3->s[2] == 7 && s3->s[3] == 10 && s3->s[4] == 15 && s3->s[5] == -1 && s3->s[SET_SIZE - 1] == -2);
	
	printf("OK\n");
}

void	test__shift_left()
{
	printf("Test shift_left\n");

	//TEST DECALAGE HORS TAILLE MAX
	struct	set* s1 = set__empty();
	assert(set__shift_left(s1, 0, SET_SIZE - 1) == FAILURE);

	//TEST DECALAGE LEGAL
	struct	set *s2 = set__empty();
	set__add(s2, 10);
	set__add(s2, 15);
	set__add(s2, 2);
	assert (set__shift_left(s2, 0, 1) == FAILURE );
	set__shift_left(s2, 1, 3);
	assert(s2->s[0] == 10 && s2->s[SET_SIZE - 1] == -2 && s2->s[1] == 15 && s2->s[2] == -1);

	printf("OK\n");
}

void	test__set__size()
{
	printf("Test set__size\n");
	
	//TEST ENSEMBLE VIDE
	struct	set* s1= set__empty();
	assert((set__size(s1) == 0));

	//Test ENSEMBLE NON VIDE
	struct	set *s2= set__empty();
	set__add(s2, 1);
	set__add(s2, 7);

	set__add(s2, 1);
	assert((set__size(s2) == 2));
	
	printf("Ok\n");
}

void	test__set__add()
{
	printf("Test set__add\n");
	
	//TEST ENSEMBLE VIDE

	struct	set *s2= set__empty();
	set__add(s2, 1);
	assert((set__size(s2) == 1) && s2->s[0] == 1 && s2->s[1] == -1 && s2->s[SET_SIZE - 1] == -2);
	set__add(s2, 1);
	assert((set__size(s2) == 1) && s2->s[0] == 1 && s2->s[1] == -1 && s2->s[SET_SIZE - 1] == -2);
	printf("Ok\n");
}

void	test__set__find()
{
	printf("Test set__find\n");
	
	//TEST ENSEMBLE VIDE
	struct	set *s1= set__empty();
	assert((set__find(s1, 7) == FAILURE));

	//Test ENSEMBLE NON VIDE
	struct	set *s2 = set__empty();
	set__add(s2, 1);
	set__add(s2, 7);
	assert(set__find(s2, 7) == 1);
	assert(set__find(s2, 1) == 0);
	assert(set__find(s2, 2) == 1);

	printf("Ok\n");
}

void	test__set__remove()
{
	printf("Test set__remove\n");
	
	//TEST ENSEMBLE VIDE
	struct	set *s1 = set__empty();
	assert((set__remove(s1, 1) == FAILURE));

	//Test ENSEMBLE NON VIDE
	struct	set *s2 = set__empty();
	set__add(s2, 1);
	set__add(s2, 7);
	assert((set__remove(s2, 1) == 1));
	
	assert( (s2->s)[0] == 7);
	assert( (s2->s)[1] == -1);
		
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
