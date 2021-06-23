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

// static void	metaFromFileToDir(t_file *dir, t_file *newfile)
// {
// 	size_t	length;
// 	// t_meta	meta;

// 	dir->meta.blocksNum += newfile->stat.st_blocks;
// 	if (newfile->hasACL)
// 		dir->meta.hasACL = 1;
// 	length = countRanksSizeT(newfile->stat.st_nlink, 10); // calcIntItoaLength
// 	if (length > dir->meta.maxLinksNumLen)
// 		dir->meta.maxLinksNumLen = length;
// 	length = ft_strlen(newfile->author);
// 	if (length > dir->meta.maxAuthorLen)
// 		dir->meta.maxAuthorLen = length;
// 	length = ft_strlen(newfile->group);
// 	if (length > dir->meta.maxGroupLen)
// 		dir->meta.maxGroupLen = length;
// 	if (file->stat.st_size == 0 && file->stat.st_rdev != 0)
// 		length = calcDeviceMajorMinorLength(file).maxSizeLen;
// 	else
// 		length = countRanksSizeT(newfile->stat.st_size, 10);
// 	if (length > dir->meta.maxSizeLen)
// 		dir->meta.maxSizeLen = length;
	
// 	// length = countRanksSizeT(newfile->stat.st_size, 10); // calcIntItoaLength
	
// }

static void	metaExchange(t_file *dir, t_file *newfile)
{
	size_t	length;
	t_meta  fileMeta;

	newfile->isNeedQuotes = dir->isNeedQuotes;
	if (newfile->author == NULL || newfile->group == NULL)
		return ;
	dir->meta.blocksNum += newfile->stat.st_blocks;
	if (newfile->hasACL)
		dir->meta.hasACL = 1;
	length = countRanksSizeT(newfile->stat.st_nlink, 10);
	if (length > dir->meta.maxLinksNumLen)
		dir->meta.maxLinksNumLen = length;
	length = ft_strlen(newfile->author);
	if (length > dir->meta.maxAuthorLen)
		dir->meta.maxAuthorLen = length;
	length = ft_strlen(newfile->group);
	if (length > dir->meta.maxGroupLen)
		dir->meta.maxGroupLen = length;
	if (newfile->stat.st_size == 0 && newfile->stat.st_rdev != 0)
	{
		fileMeta = calcDeviceMajorMinorLength(newfile);
		if (fileMeta.maxMajorLen > dir->meta.maxMajorLen)
			dir->meta.maxMajorLen = fileMeta.maxMajorLen;
		if (fileMeta.maxMinorLen > dir->meta.maxMinorLen)
			dir->meta.maxMinorLen = fileMeta.maxMinorLen;
		if (dir->meta.maxMajorLen + 2 + dir->meta.maxMinorLen > dir->meta.maxSizeLen)
			dir->meta.maxSizeLen = dir->meta.maxMajorLen + 2 + dir->meta.maxMinorLen;
	}
		
	else
	{
		length = countRanksSizeT(newfile->stat.st_size, 10);
		if (length > dir->meta.maxSizeLen)
			dir->meta.maxSizeLen = length;
	}
	dir->meta.sum = dir->meta.maxLinksNumLen + dir->meta.maxAuthorLen + \
		dir->meta.maxGroupLen + dir->meta.maxSizeLen + dir->meta.hasACL;
}

void	insertByFlags(int flags, t_file *dir, t_file *newfile)
{
	metaExchange(dir, newfile);
	if (flags & (1 << FLAG_R))
	{
		if (flags & (1 << FLAG_T))
			insert(dir, newfile, insertByModTimeReverse);
		else if (flags & (1 << FLAG_U))
			insert(dir, newfile, insertByAccessTimeReverse);
		else if (!(flags & (1 << FLAG_F)))
			insert(dir, newfile, insertByNameReverse);
		else
			insert(dir, newfile, insertWithoutOrder);
	}
	else
	{
		if (flags & (1 << FLAG_T))
			insert(dir, newfile, insertByModTime);
		else if (flags & (1 << FLAG_U))
			insert(dir, newfile, insertByAccessTime);
		else if (!(flags & (1 << FLAG_F)))
			insert(dir, newfile, insertByName);
		else
			insert(dir, newfile, insertWithoutOrder);
	}
}
