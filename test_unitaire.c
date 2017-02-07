#include "set_sentinel.h"
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
	assert(!set__is_empty(&s2));
	
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
	set__add(&s1, 10);
	set__shift_right(&s1, 0, 1);
	assert(s1.s[1] == 10 && s1.s[SET_SIZE - 1] == -2 && s1.s[3] == -1);
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
	set__add(&s1, 10);
	set__add(&s1, 15);
	set__shift_right(&s1, 0, 2);
	assert(s1.s[1] == 15 && s1.s[SET_SIZE - 1] == -2 && s1.s[2] == -1);
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
	test__set__add();
	test__set__find();	
	test__set__remove();
	return (0);
}
