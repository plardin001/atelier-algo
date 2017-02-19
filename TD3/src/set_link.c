
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

struct set	*set__empty(void)
{
	struct	link	*l;
	struct	set	*s;

	s = (struct set *)malloc(sizeof(struct set));
	if (s == NULL)
		return (NULL);
	l = (struct link *)malloc(sizeof(struct link));
	if (l == NULL)
	{
		free(s);
		return (NULL);
	}
	s->l = l;
	lnk__empty(s->l);
	return (s);
}

int	set__is_empty(struct set const *s)
{
	if (s == NULL || s->l == NULL || s->l->head == NULL)
		return (0);
	return ((llm__is_end_mark(s->l->head)));
}

int	set__find(struct set const* s, int val)
{
	struct lelement *tmp;

	if (s == NULL || s->l == NULL || s->l->head == NULL)
		return (0);
	tmp = lnk__first(s->l);
	while (!llm__is_end_mark(tmp))
	{
		if (tmp->data == val)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	set__size(struct set const *s)
{
	struct lelement *tmp;
	int		i;

	i = 0;
	if (s == NULL || s->l == NULL || s->l->head == NULL)
		return (i);
	tmp = lnk__first(s->l);
	while (!llm__is_end_mark(tmp))
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}



int	set__add(struct set *s, int val)
{
	struct lelement *new;
	struct lelement *tmp;

	if (s == NULL || s->l == NULL || set__find(s, val))
		return (0);
	new = (struct lelement *)malloc(sizeof(struct lelement));
	new->data = val;
	if (new == NULL)
		return (0);
	tmp = lnk__first(s->l);
	if (llm__is_end_mark(tmp))
	{
		lnk__add_head(s->l, new);
		return (1);
	}
	while (!llm__is_end_mark(tmp->next) && !(tmp->next->data >= val))
	{
		tmp = tmp->next;
	}
	lnk__add_after(s->l, tmp, new);
	return (1);
	

}

int	set__remove(struct set *s, int val)
{
	struct lelement *del;
	struct lelement *tmp;

	if (s == NULL || s->l == NULL)
		return (0);
	tmp = lnk__first(s->l);
	if (llm__is_end_mark(tmp))
		return (0);
	while (!llm__is_end_mark(tmp->next) && !(tmp->next->data >= val))
	{
		tmp = tmp->next;
	}
	if (tmp->data != val)
		return (0);
	del = lnk__remove_after(s->l, tmp);
	free(del);
	return (1);
}


void	set__free(struct set **s)
{
	struct	lelement *tmp;
	struct	lelement *next;

	if (s == NULL || *s == NULL)
		return ;
	if ((*s)->l == NULL)
	{
		free(*s);
		return ;
	}
	if ((*s)->l->head == NULL)
	{
		free((*s)->l);
		free(*s);
		return ;
	}
	tmp = (*s)->l->head;
	while (!llm__is_end_mark(tmp))
	{
		next = tmp->next;
		free(tmp);
		tmp = next;		
	}
	free(tmp);
	free((*s)->l);
	free(*s);
	return ;
}
