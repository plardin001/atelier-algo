#include "set_sentinel.h"

#define SUCCESS 1
#define FAILURE 0
#define ERROR -1


void	set__empty(struct set *a)
{	
        if(a == NULL)
	        return ;
  	(a->s)[0] = -1;
  	(a->s)[SET_SIZE - 1] = -2;
	return ;
}

int	set__is_empty(struct set const *a)
{
	if (a == NULL)
		return (ERROR);
	if ((a->s)[0] == -1)
		return (SUCCESS);
	return (FAILURE);
}

int	set__find(struct set const *a, int val) //retrun the right position of val 
{
	int	size;
	int	begin;
	int	end;
	int	mid;
	
	size = set__size(a);
	begin = 0;
	end = size - 1;
	if (size == 0 || a == NULL || val < 0)
		return (ERROR);
	while (end != begin)
	{
		mid = (begin + end) / 2; 
		if (end - begin == 1 || end - begin == 0)
		{
			if ((a->s)[begin] ==  val)
				return (begin);
			else
				return (end);
		}
		if (val > (a->s)[mid])
			 begin = mid;
		else if ((a->s)[mid] == val)
			return (mid);
		else 
			end = mid;
	} 
	return (ERROR);
}

int	set__shift_right(struct set *a, int i, int j) //i first index to move right and j last index to move right
{
	if (j + 2 > SET_SIZE || (a->s)[j + 2] == -2)
		return (FAILURE);
	(a->s)[j + 2] = -1;
	for(int k = j; k >= i; k--)
		(a->s)[k + 1] = (a->s)[k];				
	return (SUCCESS);
}

int	set__shift_left(struct set *a, int i, int j) //i first index to move left and j last index to move right (if i = 0, the value is lost, else, the value i-1 is lost)
{
        if (i != 0)
	        (a->s)[i - 1] = (a->s)[i];
	for(int k = i; k <= j; k++)
		(a->s)[k] = (a->s)[k + 1];
	if (j == SET_SIZE - 1)
	        (a->s)[j] = -2;
	else
	        (a->s)[j] = -1;
	return (SUCCESS);
}
	
int	set__size(struct set const *a)
{
	int	j;
	
	for (j = 0; j <= SET_SIZE; j++)
	{
		if ((a->s)[j] <= -1)
			return (j);	
	}
	return (ERROR);
}
	
int	set__add(struct set *a, int val)
{
	int	i;
	int     size;

	i = set__find(a, val);
	size = set__size(a);
	set__shift_right(a, i, size);
	(a->s)[i] = val;
	return (SUCCESS);
	
}

int	set__remove(struct set *a, int val)
{
        int	j;

	j = set__find(a, val);
	set__shift_left(a, 0, j);
	(a->s)[j] = val;
	return (SUCCESS);
}
