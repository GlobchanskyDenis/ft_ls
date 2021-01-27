#include "ft_ls.h"

static void	insert(t_file *dir, t_file *newfile,
	int (*insert)(t_file *dir, t_file *prev, t_file *next, t_file *node))
{
	t_file *node;

	if (dir->child == NULL)
		dir->child = newfile;
	else
	{
		node = dir->child;
		while (!(insert(dir, node, node->next, newfile)))
			node = node->next;
	}
}

void		insertByFlags(int flags, t_file *dir, t_file *newfile)
{
	newfile->isNeedQuotes = dir->isNeedQuotes;
	if (flags & FLAG_R)
	{
		if (flags & FLAG_T)
			insert(dir, newfile, insertByModTimeReverse);
		else if (flags & FLAG_U)
			insert(dir, newfile, insertByAccessTimeReverse);
		else if (!(flags & FLAG_F))
			insert(dir, newfile, insertByNameReverse);
		else
			insert(dir, newfile, insertWithoutOrder);
	}
	else
	{
		if (flags & FLAG_T)
			insert(dir, newfile, insertByModTime);
		else if (flags & FLAG_U)
			insert(dir, newfile, insertByAccessTime);
		else if (!(flags & FLAG_F))
			insert(dir, newfile, insertByName);
		else
			insert(dir, newfile, insertWithoutOrder);
	}
}

