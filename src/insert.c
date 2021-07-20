#include "ft_ls.h"

/*
**	This functions inserting file into file tree
**	guided by the method of sorting the given flags
*/

static void	insert(t_file *dir, t_file *newfile,
	int (*insert)(t_file *dir, t_file *prev, t_file *next, t_file *node))
{
	t_file	*node;

	if (dir->child == NULL)
		dir->child = newfile;
	else
	{
		node = dir->child;
		while (!(insert(dir, node, node->next, newfile)))
			node = node->next;
	}
}

static void	insertReverse(int flags, t_file *dir, t_file *newfile)
{
	if (isSortingDisabled(flags))
		insert(dir, newfile, insertWithoutOrder);
	else if (flags & (1 << SORT_BY_MODIF))
	{
		if (flags & (1 << FLAG_FILE_ARGS))
			insert(dir, newfile, insertByModTimeReverseNameDesc);
		else
			insert(dir, newfile, insertByModTimeReverseNameDesc);
	}
	else if (flags & (1 << SORT_BY_ACCESS))
	{
		if (!newfile->isArgument)
			insert(dir, newfile, insertByAccessTimeReverse);
		else
			insert(dir, newfile, insertWithoutOrder);
	}
	else if (flags & (1 << SORT_BY_NAME))
		insert(dir, newfile, insertByNameReverse);
	else
		fprint("Рефакторинг!!! insertByFlags found unexpected case!!\n");
}

static void	insertInRightOrder(int flags, t_file *dir, t_file *newfile)
{
	if (isSortingDisabled(flags))
		insert(dir, newfile, insertWithoutOrder);
	else if (flags & (1 << SORT_BY_MODIF))
	{
		if (flags & (1 << FLAG_FILE_ARGS))
			insert(dir, newfile, insertByModTimeNameDesc);
		else
			insert(dir, newfile, insertByModTimeNameDesc);
	}
	else if (flags & (1 << SORT_BY_ACCESS))
	{
		if (!newfile->isArgument)
			insert(dir, newfile, insertByAccessTime);
		else
			insert(dir, newfile, insertWithoutOrder);
	}
	else if (flags & (1 << SORT_BY_NAME))
		insert(dir, newfile, insertByName);
	else
		fprint("Рефакторинг!!! insertByFlags found unexpected case!!\n");
}

/*	Исключение для сортировки по времени доступа (-u)
**	Если файлы были поданы как аргумент CLI - это блокирует
**	выполнение флага -u  */

void	insertByFlags(int flags, t_file *dir, t_file *newfile)
{
	metaExchange(dir, newfile);
	if (flags & (1 << FLAG_R))
		insertReverse(flags, dir, newfile);
	else
		insertInRightOrder(flags, dir, newfile);
}
