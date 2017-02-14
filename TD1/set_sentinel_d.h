#ifndef SET_SENTINEL_D_H
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
