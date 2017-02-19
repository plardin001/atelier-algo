#ifndef SET_LINK_H
# define SET_LINK_H
#include "link.h"



struct set *set__empty(void);
int	set__is_empty(struct set const *s);
int	set__find(struct set const* s, int val);
int	set__size(struct set const *s);
int	set__add(struct set *s, int val);
int	set__remove(struct set *s, int val);
#endif
