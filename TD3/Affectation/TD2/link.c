#include "link.h"
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
