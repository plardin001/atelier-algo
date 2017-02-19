#include "set_sentinel_d.h"
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
