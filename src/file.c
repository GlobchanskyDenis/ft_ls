#include "ft_ls.h"

/*	Constructor and handlers for t_file file type  */

t_file	*newFile(char const *name, char *fullpath, int type)
{
	t_file	*dst;

	if (name == NULL && fullpath != NULL)
		ft_strdel(&fullpath);
	if (fullpath == NULL)
		return (NULL);
	dst = (t_file *)ft_memalloc(sizeof(t_file));
	if (!dst)
		return (NULL);
	dst->type = type;
	ft_strcpy(dst->name, name);
	dst->isNeedNameQuotes = initAlternateString(dst->alterName, dst->name);
	dst->fullpath = fullpath;
	return (dst);
}

void	freeFile(t_file **file)
{
	if (file == NULL || *file == NULL)
		return ;
	if ((*file)->fullpath != NULL)
		free((*file)->fullpath);
	if ((*file)->symlink != NULL)
		free((*file)->symlink);
	free(*file);
	*file = NULL;
}

int	calcOnlyDirectories(t_file *file)
{
	int	i;

	i = 0;
	while (file)
	{
		if (file->type == DIRECTORY)
			i++;
		file = file->next;
	}
	return (i);
}

int	calcOnlyDirectoriesThatWeCanAccess(t_file *file)
{
	int	i;

	i = 0;
	while (file)
	{
		if (file->type == DIRECTORY && file->accessErrno == 0)
			i++;
		file = file->next;
	}
	return (i);
}

int	calcOnlyNotDirectories(t_file *file)
{
	int	i;

	i = 0;
	while (file)
	{
		if (file->type != DIRECTORY)
			i++;
		file = file->next;
	}
	return (i);
}
