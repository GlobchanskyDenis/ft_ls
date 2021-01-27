#include "ft_ls.h"

static void	insertToNext(t_file **head, t_file *newfile,
	int (*insert)(t_file **prev, t_file *next, t_file *node))
{
	t_file *node;

	// fprint("insertToNext function\n");
	// DumpFileTree(0, *head);
	if (insert(head, (*head)->next, newfile))
	{
		// fprint("inserted in head!!\n");
		// DumpFileTree(0, *head);
		return ;
	}
	else
	{
		node = *head;
		while (!(insert(&node, node->next, newfile)))
			node = node->next;
		// fprint("inserted in tail\n");
		// DumpFileTree(0, *head);
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
	{
		if (flags & FLAG_T)
			insertToNext(head, newfile, insertNextByModTimeReverse);
		else if (flags & FLAG_U)
			insertToNext(head, newfile, insertNextByAccessTimeReverse);
		else if (!(flags & FLAG_F))
			insertToNext(head, newfile, insertNextByNameReverse);
		else
			insertToNext(head, newfile, insertNextWithoutOrder);
	}
	else
	{
		if (flags & FLAG_T)
			insertToNext(head, newfile, insertNextByModTime);
		else if (flags & FLAG_U)
			insertToNext(head, newfile, insertNextByAccessTime);
		else if (!(flags & FLAG_F))
			insertToNext(head, newfile, insertNextByName);
		else
			insertToNext(head, newfile, insertNextWithoutOrder);
	}

	// if (flags & FLAG_R)
	//	insertToNext(head, newfile, insertNextByNameReverse);
	// else
	//	insertToNext(head, newfile, insertNextByName);
}

void		insertToChildsByFlags(int flags, t_file *dir, t_file *newfile)
{
	if (flags & FLAG_R)
	{
		if (flags & FLAG_T)
			insertToChilds(dir, newfile, insertByModTimeReverse);
		else if (flags & FLAG_U)
			insertToChilds(dir, newfile, insertByAccessTimeReverse);
		else if (!(flags & FLAG_F))
			insertToChilds(dir, newfile, insertByNameReverse);
		else
			insertToChilds(dir, newfile, insertWithoutOrder);
	}
	else
	{
		if (flags & FLAG_T)
			insertToChilds(dir, newfile, insertByModTime);
		else if (flags & FLAG_U)
			insertToChilds(dir, newfile, insertByAccessTime);
		else if (!(flags & FLAG_F))
			insertToChilds(dir, newfile, insertByName);
		else
			insertToChilds(dir, newfile, insertWithoutOrder);
	}
}

