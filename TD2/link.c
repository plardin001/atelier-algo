#include "link.h"

void				lnk__empty(struct link *a)
{
	if (a == NULL || a->head == NULL)
		return ;
	a->head->next = a->head;
}

struct lelement		*lnk__first(struct link *a)
{
	if (a == NULL)
		return (NULL);
	return (a->head);
}


int					llm__is_end_mark(struct lelement *is_sentinel)
{
	if (is_sentinel == NULL)
		return (0);
	return (is_sentinel->next == is_sentinel);
}

void				lnk__add_head(struct link *a, struct lelement *new)
{
	struct lelement *head;
	
	if (a == NULL || a->head == NULL || new == NULL)
		return ;
	new->next = a->head;
	a->head = new;
}

struct lelement		*lnk__remove_head(struct link *a)
{
	struct lelement	*head;
	struct lelement	*next;
	struct lelement	*del;

	if (a == NULL || a->head == NULL)
		return (NULL);
	del = a->head;
	a->head->next = next;
	a->head = next;
	return (del);
}

struct lelement		*llm__next(struct lelement *a)
{
	if (a == NULL)
		return (NULL);
	if (a->next == a)
		return (a);
	else
		return (a->next);
}

struct lelement		*lnk__add_after(struct link *lst, struct lelement *begin, struct lelement *new)
{
	struct lelement *tmp;
	struct lelement *next;

	if (lst == NULL || lst->head == NULL || begin == NULL || begin->next == begin || new == NULL)
		return (NULL);
	next = begin->next;
	begin->next = new;
	new->next = next;
	return (new);
}

struct lelement		*lnk__remove_after(struct link *lst, struct lelement *begin, struct lelement *new)
{
	struct lelement *del;
	struct lelement *next;
	struct lelement *tmp;

	if (lst == NULL || lst->head == NULL || begin == NULL || begin->next == begin || new == NULL)
		return (NULL);
	tmp = lst->head;
	while (tmp != begin)
	{
		if (tmp->next == tmp)
			return (NULL);
		tmp = tmp->next;
	}
	del = begin->next;
	next = del->next;
	begin ->next = next;
	return (del);
}

void			lnk__add_tail(struct link *lst, struct lelement *new)
{
	struct lelement *del;
	struct lelement *next;
	struct lelement *tmp;

	if (lst == NULL || lst->head == NULL || new == NULL)
		return ;
	tmp = lst->head;
	if (tmp->next = tmp)
	{
		lst->head = new;
		new->next = tmp;
		return ;
	}
	while (tmp->next->next != tmp->next)
	{
		tmp = tmp->next;
	}
	next = tmp->next;
	tmp->next = new;
	new->next = tmp;
}

struct lelement			*lnk__remove_tail(struct link *lst, struct lelement *new)
{
	struct lelement *del;
	struct lelement *sentinel;
	struct lelement *tmp;

	if (lst == NULL || lst->head == NULL || new == NULL || lst->head->next == lst->head )
		return (NULL);
	tmp = lst->head;
	if (tmp->next->next = tmp->next)
	{
		del = tmp->next;
		lst->head->next = lst->head;
		return (del);
	}
	while (tmp->next->next->next != tmp->next->next)
	{
		tmp = tmp->next;
	}
	del = tmp->next;
	sentinel = tmp->next->next;
	tmp->next = sentinel;
	return (del);
}
