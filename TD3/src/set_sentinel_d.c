#include <stdlib.h>

struct set
{
	int	*s;
	size_t	capacity;
	size_t	size;	
};


#include "set.h"


struct set	*set__empty(void)
{
		struct set *a;

		a = (struct set *)malloc(sizeof(struct set));
		if (a == NULL)
			return (NULL);
		a->size = 0;
		a->s = NULL;
		a->capacity = 0;
		return (a);
}

int		set__is_empty(struct set const *a)
{
		if (a == NULL)
			return (0);
		else if (a->size == 0)
			return (1);
		else
			return (0);
}


int		set__size(struct set const *a)
{
	if (a == NULL)
		return (0);
	return (a->size);
}

int		find(struct set const *a, int val)
{
	int	debut;
	int	fin;
	int	mid;
	int	size;

		size = set__size(a);
		if (size == 0 || a == NULL || val < 0)
			return (0);
		debut = 0;
		fin = size - 1;
		while ((fin - debut) > 1)
		{
			mid = (fin + debut) / 2;
			if ((a->s)[mid] == val)
				return (mid);
			else if ((a->s)[mid] > val)
				fin = mid;
			else
				debut = mid;
		}
		if (val > (a->s)[debut])
			return (debut + 1);
		else
			return (debut);
}

int		set__find(struct set const *a, int val)
{
	return ((a->s)[find(a, val)] == val);
}


int					shift_right(struct set *a, unsigned int i, unsigned int j)
{
	size_t			capacity;
	unsigned int	pos;

	pos = j + 1;
	capacity = (a->capacity);
	if (a == NULL || a->s == NULL || (j - i) > capacity || j > capacity || i > capacity || j + 1 > capacity)
		return (0);
	while (pos > i)
	{
		(a->s)[pos] = (a->s)[pos - 1];
		pos--;
	}
	return (1);
}


int					shift_left(struct set *a, unsigned int i, unsigned int j)
{
	size_t			capacity;
	unsigned int	pos;

	pos = i - 1;
	capacity = (a->capacity);
	if (a == NULL || a->s == NULL || (j - i) > capacity  || i ==  0)
		return (0);
	while (pos < j)
	{
		(a->s)[pos] = (a->s)[pos + 1];
		pos++;
	}
	return (1);
}

int		set__add(struct set *a, int val)
{
	unsigned int		pos;

	if (a == NULL)
		return (0);
	pos = find(a, val);
	if ((a->capacity) > pos && (a->s)[pos] == val)
		return (1);
	if (a->size == a->capacity)
	{
		if (a->capacity == 0)
			a->capacity += 1;
		else
			a->capacity *= 2;
		(a->s) = (int *)realloc(a->s, a->capacity);
		if (a == NULL)
			return (0);
	}
	shift_right(a, pos, a->size - 1);
	(a->s)[pos] = val;
	(a->size) += 1;
	return (1);
}

int		set__remove(struct set *a, int val)
{
	unsigned int		pos;

	if (a == NULL)
		return (0);
	pos = find(a, val);
	if (a->size == 0 || ((a->capacity) > pos && (a->s)[pos] != val))
		return (1);
	shift_left(a, pos + 1, a->size - 1);
	(a->size) -= 1;
	if (a->size - 1 == a->capacity / 2)
		a->capacity /= 2;
	(a->s) = (int *)realloc(a->s, a->capacity);
	if (a == NULL)
		return (0);
	return (1);
}

int	ft_filter(int element)
{
	return (element % 2);
}


struct set	*set__filter(const struct set *a, int (*f)(int))
{
	struct set	*s;
	size_t		i;

	i = 0;
	if (a == NULL)
		return (NULL);
	s = set__empty();
	while (i < a->size)
	{
		if ((*f)(a->s[i]))
			set__add(s, (a->s)[i]);
		i++;
	}
	return (s);
	
		
}

void	set__free(struct set **a)
{
	if (a == NULL || *a == NULL)
		return ;
	if ((*a)->s != NULL)
		free((*a)->s);
	free(*a);
}
