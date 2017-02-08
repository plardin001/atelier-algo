#ifndef LINK_H
#define LINK_H
#include <stdlib.h>
#include <stdio.h>

struct lelement
{
	int				data;
	struct lelement	*next;
};

struct	link
{
	struct lelement *head;
};

#endif
