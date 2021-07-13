#include "ft_ls.h"

/*
**	Algorithm returns 1 in case of insert was successfull and 0 in case of
**	inserting in this plase is not needed.
**	Algorithm sorts files by access time
*/

int	insertByAccessTimeReverse(t_file *dir, t_file *prev, t_file *next, t_file *newfile)
{
	int	ret1;
	int	ret2;
	int	ret3;

	ret1 = dir->child->stat.st_atime - newfile->stat.st_atime;
	if (ret1 > 0)
		return (insertNewFileAsFirstInFolder(dir, newfile));
	ret2 = ft_strcmp(dir->child->alterName, newfile->alterName);
	ret3 = ft_strcmp(dir->child->name, newfile->name);
	if ((ret1 == 0 && ret2 < 0) || (ret1 == 0 && ret2 == 0 && ret3 < 0))
		return (insertNewFileAsFirstInFolder(dir, newfile));
	if (next == NULL)
		return (insertNewFileAsLastInFolder(prev, newfile));
	ret1 = next->stat.st_atime - newfile->stat.st_atime;
	if (ret1 > 0)
		return (insertNewFileBetweenPrevAndNext(prev, next, newfile));
	ret2 = ft_strcmp(next->alterName, newfile->alterName);
	ret3 = ft_strcmp(next->name, newfile->name);
	if ((ret1 == 0 && ret2 < 0) || (ret1 == 0 && ret2 == 0 && ret3 < 0))
		return (insertNewFileBetweenPrevAndNext(prev, next, newfile));
	return (0);
}

int	insertByAccessTime(t_file *dir, t_file *prev, t_file *next, \
	t_file *newfile)
{
	int	ret1;
	int	ret2;
	int	ret3;

	ret1 = dir->child->stat.st_atime - newfile->stat.st_atime;
	if (ret1 < 0)
		return (insertNewFileAsFirstInFolder(dir, newfile));
	ret2 = ft_strcmp(dir->child->alterName, newfile->alterName);
	ret3 = ft_strcmp(dir->child->name, newfile->name);
	if ((ret1 == 0 && ret2 > 0) || (ret1 == 0 && ret2 == 0 && ret3 > 0))
		return (insertNewFileAsFirstInFolder(dir, newfile));
	if (next == NULL)
		return (insertNewFileAsLastInFolder(prev, newfile));
	ret1 = next->stat.st_atime - newfile->stat.st_atime;
	if (ret1 < 0)
		return (insertNewFileBetweenPrevAndNext(prev, next, newfile));
	ret2 = ft_strcmp(next->alterName, newfile->alterName);
	ret3 = ft_strcmp(next->name, newfile->name);
	if ((ret1 == 0 && ret2 > 0) || (ret1 == 0 && ret2 == 0 && ret3 > 0))
		return (insertNewFileBetweenPrevAndNext(prev, next, newfile));
	return (0);
}
