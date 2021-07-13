#include "ft_ls.h"

/*
**	Constructor and handlers for t_file file type
*/

t_file	*newFile(char const *name, char *fullpath, int type, int flags)
{
	t_file	*dst;
	size_t	nameLen;

	if (name == NULL && fullpath != NULL)
		ft_strdel(&fullpath);
	if (fullpath == NULL)
		return (NULL);
	dst = (t_file *)ft_memalloc(sizeof(t_file));
	if (!dst)
		return (NULL);
	dst->type = type;
	nameLen = ft_strlen(name);
	dst->name = (char *)malloc(nameLen * 2 + 2);
	if (!dst->name)
	{
		freeFile(&dst);
		return (NULL);
	}
	ft_strcpy(dst->name, name);
	dst->alterName = &(dst->name[nameLen + 1]);
	dst->isNeedQuotes = initAlternateString(dst->alterName, dst->name, flags);
	dst->fullpath = fullpath;
	ft_bzero(dst->devId, MAX_DEVICESIZE + 1);
	return (dst);
}

void	freeFile(t_file **file)
{
	if (file == NULL || *file == NULL)
		return ;
	if ((*file)->name != NULL)
		free((*file)->name);
	if ((*file)->fullpath != NULL)
		free((*file)->fullpath);
	if ((*file)->symlink != NULL)
		free((*file)->symlink);
	free(*file);
	*file = NULL;
}

int	isFileNotExist(char const *filename)
{
	struct stat	stat;

	if (lstat(filename, &stat) != 0)
		return (errno);
	return (0);
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
