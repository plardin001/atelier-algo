#ifndef SET_H
# define SET_H

#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define ERROR -1

struct set*	set__empty();
int	set__is_empty(struct set const *);
int	set__find(struct set const*, int val);
int	set__shift_right(struct set *a, int i, int j);
int	set__shift_left(struct set *a, int i, int j);
int	set__size(struct set const*);
int	set__add(struct set *, int val);
int	set__remove(struct set *, int val);
void	set__free(struct set **);
#endif
