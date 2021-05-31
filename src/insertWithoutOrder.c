#include "ft_ls.h"

/*
**	Algorithm returns 1 in case of insert was successfull and 0 in case of
**	inserting in this plase is not needed.
**	The algorithm does not sort the files, but adds them in the order of arrival
*/

int insertWithoutOrder(t_file *dir, t_file *prev, t_file *next, t_file *node)
{
	if (next != NULL)
		return (0);
	if (prev != NULL)
	{
		prev->next = node;
		return (1);
	}
	dir->child = node;
	return (1);
}

