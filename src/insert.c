#include "ft_ls.h"

static void	insertToNext(t_file **head, t_file *newfile,
	int (*insert)(t_file **prev, t_file *next, t_file *node))
{
	t_file *node;

	if (insert(head, (*head)->next, newfile))
		return ;
	else
	{
		node = *head;
		while (!(insert(&node, node->next, newfile)))
			node = node->next;
	}
}

static void	insertToChilds(t_file *dir, t_file *newfile,
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

void		insertToNextByFlags(int flags, t_file **head, t_file *newfile)
{
	if (flags & FLAG_R)
		insertToNext(head, newfile, insertNextByNameReverse);
	else
		insertToNext(head, newfile, insertNextByName);
}

void		insertToChildsByFlags(int flags, t_file *dir, t_file *newfile)
{
	if (flags & FLAG_R)
		insertToChilds(dir, newfile, insertByNameReverse);
	else
		insertToChilds(dir, newfile, insertByName);
}

