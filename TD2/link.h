#ifndef LINK_H
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
