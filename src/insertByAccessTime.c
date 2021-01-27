#include "ft_ls.h"

/*
**	Алгоритм проверки вставлять ли в данное место новый файл
*/
int insertByAccessTime(t_file *dir, t_file *prev, t_file *next, t_file *node)
{
	int		ret;

	if ((ret = (dir->child->stat.st_atime - node->stat.st_atime)) > 0 ||
		(ret == 0 && (ret = ft_strcmp(dir->child->alterName, node->alterName))
		> 0) || (ret == 0 && ft_strcmp(dir->child->name, node->name) < 0))
	{
		// fprint("files: %s %s ret %d\n", dir->child->alterName, node->alterName, ret);
		node->next = dir->child;
		dir->child = node;
		return (1);
	}
	if (next == NULL)
	{
		prev->next = node;
		return (1);
	}
	if ((ret = next->stat.st_atime - node->stat.st_atime) > 0 ||
		(ret == 0 && (ret = ft_strcmp(next->alterName, node->alterName))
		> 0) || (ret == 0 && ft_strcmp(next->name, node->name) < 0))
	{
		// fprint("files: %s %s ret %d\n", next->alterName, node->alterName, ret);
		node->next = next;
		prev->next = node;
		return (1);
	}
	return (0);
}

int insertByAccessTimeReverse(t_file *dir, t_file *prev, t_file *next,
		t_file *node)
{
	int		ret;

	if ((ret = (dir->child->stat.st_atime - node->stat.st_atime)) < 0 ||
		(ret == 0 && (ret = ft_strcmp(dir->child->alterName, node->alterName))
		< 0) || (ret == 0 && ft_strcmp(dir->child->name, node->name) > 0))
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
	if ((ret = next->stat.st_atime - node->stat.st_atime) < 0 ||
		(ret == 0 && (ret = ft_strcmp(next->alterName, node->alterName)) < 0) ||
		(ret == 0 && ft_strcmp(next->name, node->name) > 0))
	{
		node->next = next;
		prev->next = node;
		return (1);
	}
	return (0);
}

int insertNextByAccessTime(t_file **prev, t_file *next, t_file *node)
{
	int		ret;

	if ((ret = ((*prev)->stat.st_atime - node->stat.st_atime)) > 0 ||
		(ret == 0 && (ret = ft_strcmp((*prev)->alterName, node->alterName)) > 0)
		|| (ret == 0 && ft_strcmp((*prev)->name, node->name) < 0))
	{
		node->next = *prev;
		*prev = node;
		return (1);
	}
	if (next == NULL)
	{
		(*prev)->next = node;
		return (1);
	}
	if ((ret = next->stat.st_atime - node->stat.st_atime) > 0 ||
		(ret == 0 && (ret = ft_strcmp(next->alterName, node->alterName)) > 0)
		|| (ret == 0 && ft_strcmp(next->name, node->name) < 0))
	{
		node->next = next;
		(*prev)->next = node;
		return (1);
	}
	return (0);
}

int insertNextByAccessTimeReverse(t_file **prev, t_file *next, t_file *node)
{
	int		ret;

	if ((ret = ((*prev)->stat.st_atime - node->stat.st_atime)) < 0 ||
		(ret == 0 && (ret = ft_strcmp((*prev)->alterName, node->alterName)) < 0)
		|| (ret == 0 && ft_strcmp((*prev)->name, node->name) > 0))
	{
		node->next = *prev;
		*prev = node;
		return (1);
	}
	if (next == NULL)
	{
		(*prev)->next = node;
		return (1);
	}
	if ((ret = next->stat.st_atime - node->stat.st_atime) < 0 ||
		(ret == 0 && (ret = ft_strcmp(next->alterName, node->alterName)) < 0) ||
		(ret == 0 && ft_strcmp(next->name, node->name) > 0))
	{
		node->next = next;
		(*prev)->next = node;
		return (1);
	}
	return (0);
}

