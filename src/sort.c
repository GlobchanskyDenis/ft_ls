#include "ft_ls.h"

/*
**	 Алгоритм проверки вставлять ли в данное место новый файл
*/
int insertByName(t_file *dir, t_file *prev, t_file *next, t_file *node)
{
	if (ft_strcmpOneCase(dir->child->name, node->name) >= 0)
	{
		node->next = dir->child;
		dir->child = node;
		return (1);
	}
	if (next == NULL)
	{
		prev->next = node;
		return (1);
	}
	if (ft_strcmpOneCase(next->name, node->name) >= 0)
	{
		node->next = next;
		prev->next = node;
		return (1);
	}
	return (0);
}

int insertByNameReverse(t_file *dir, t_file *prev, t_file *next, t_file *node)
{
	if (ft_strcmpOneCase(dir->child->name, node->name) <= 0)
	{
		node->next = dir->child;
		dir->child = node;
		return (1);
	}
	if (next == NULL)
	{
		prev->next = node;
		return (1);
	}
	if (ft_strcmpOneCase(next->name, node->name) <= 0)
	{
		node->next = next;
		prev->next = node;
		return (1);
	}
	return (0);
}