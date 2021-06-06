#include "ft_ls.h"

/*
**	This functions inserting file into file tree
**	guided by the method of sorting the given flags
*/

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

static size_t	calcIntItoaLength(int nbr)
{
	size_t	length;

	length = 1;
	while ((nbr = nbr / 10))
		length++;
	return (length);
}

static void	metaExchange(t_file *dir, t_file *newfile)
{
	size_t	length;

	newfile->isNeedQuotes = dir->isNeedQuotes;
	if (newfile->author == NULL || newfile->group == NULL)
		return ;
	dir->meta.blocksNum += newfile->stat.st_blocks;
	if (newfile->hasACL)
		dir->meta.hasACL = 1;
	length = calcIntItoaLength(newfile->stat.st_nlink);
	if (length > dir->meta.maxLinksNumLen)
		dir->meta.maxLinksNumLen = length;
	length = ft_strlen(newfile->author);
	if (length > dir->meta.maxAuthorLen)
		dir->meta.maxAuthorLen = length;
	length = ft_strlen(newfile->group);
	if (length > dir->meta.maxGroupLen)
		dir->meta.maxGroupLen = length;
	length = calcIntItoaLength(newfile->stat.st_size);
	if (length > dir->meta.maxSizeLen)
		dir->meta.maxSizeLen = length;
	dir->meta.sum = dir->meta.maxLinksNumLen + dir->meta.maxAuthorLen +
		dir->meta.maxGroupLen + dir->meta.maxSizeLen + dir->meta.hasACL;
}

void		insertByFlags(int flags, t_file *dir, t_file *newfile)
{
	metaExchange(dir, newfile);
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

