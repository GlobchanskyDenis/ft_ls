#include "ft_ls.h"

/*
**	Algorithm returns 1 in case of insert was successfull and 0 in case of
**	inserting in this plase is not needed.
**	Algorithm sorts files by filenames (russian alphabet correct too)
*/

int	insertByName(t_file *dir, t_file *prev, t_file *next, t_file *newfile)
{
	int		ret;

	ret = ft_strcmp(dir->child->alterName, newfile->alterName);
	if (ret > 0 || (ret == 0 && ft_strcmp(dir->child->name, newfile->name) < 0))
		return (insertNewFileAsFirstInFolder(dir, newfile));
	if (next == NULL)
		return (insertNewFileAsLastInFolder(prev, newfile));
	ret = ft_strcmp(next->alterName, newfile->alterName);
	if (ret > 0 || (ret == 0 && ft_strcmp(next->name, newfile->name) < 0))
		return (insertNewFileBetweenPrevAndNext(prev, next, newfile));
	return (0);
}

int	insertByNameReverse(t_file *dir, t_file *prev, t_file *next, \
	t_file *newfile)
{
	int		ret;

	ret = ft_strcmp(dir->child->alterName, newfile->alterName);
	if (ret < 0 || (ret == 0 && ft_strcmp(dir->child->name, newfile->name) > 0))
		return (insertNewFileAsFirstInFolder(dir, newfile));
	if (next == NULL)
		return (insertNewFileAsLastInFolder(prev, newfile));
	ret = ft_strcmp(next->alterName, newfile->alterName);
	if (ret < 0 || (ret == 0 && ft_strcmp(next->name, newfile->name) > 0))
		return (insertNewFileBetweenPrevAndNext(prev, next, newfile));
	return (0);
}
