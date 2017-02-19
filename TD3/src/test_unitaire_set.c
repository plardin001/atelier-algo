#include <assert.h>
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

struct set
{
	struct link	*l;
};

#include "set_link.h"


void	test__set__is_empty()
{
	printf("Test set__is_empty\n");

	//TEST ENSEMBLE VIDE
	struct	set s1;
	s1 = *set__empty();
	assert(set__is_empty(&s1));
	//Test ENSEMBLE NON VIDE
	struct	set s2;

	s2 = *set__empty();
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
	s1 = *set__empty();
	assert((set__size(&s1) == 0));
	
	//Test ENSEMBLE NON VIDE
	struct	set s2;
	s2 = *set__empty();
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
	s2 = *set__empty();
	set__add(&s2, 1);
	assert(set__find(&s2, 1));
	printf("Ok\n");
}

void	test__set__find()
{
	printf("Test set__find\n");
	
	//TEST ENSEMBLE VIDE
	struct	set s1;
	s1 = *set__empty();
	assert((set__find(&s1, 7) == 0));

	//Test ENSEMBLE NON VIDE
	struct	set s2;
	s2 = *set__empty();
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
	s1 = *set__empty();
	assert((set__remove(&s1, 1) == 0));

	//Test ENSEMBLE NON VIDE
	struct	set s2;
	s2 = *set__empty();
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
