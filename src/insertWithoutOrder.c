#include "ft_ls.h"

/*
**	Алгоритм проверки вставлять ли в данное место новый файл
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
