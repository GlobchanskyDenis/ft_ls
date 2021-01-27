#include "ft_ls.h"

t_file	*newFile(char const *name, char const *path, int type)
{
	t_file	*dst;
	size_t	nameLen;

	if (!(dst = (t_file *)ft_memalloc(sizeof(t_file))))
		return (NULL);
	dst->type = type;
	if (name == NULL)
		return (dst);
	nameLen = ft_strlen(name);
	if (!(dst->name = (char *)malloc(nameLen * 2 + 2)))
	{
		freeFile(&dst);
		return NULL;
	}
	ft_strcpy(dst->name, name);
	dst->alterName = &(dst->name[nameLen + 1]);
	dst->isNeedQuotes = initAlternateString(dst->alterName, dst->name);
	dst->path = (char *)path;
	return (dst);
}

t_error	createChildFilePath(t_file *directory, char **path)
{
	if (directory->name == NULL)
		*path = NULL;
	else if (directory->path == NULL)
	{
		if ((*path = ft_strdup(directory->name)) == NULL)
			return (allocateFailed());
	}
	else
	{
		if ((*path = ft_concat3(directory->path, "/",
			directory->name)) == NULL)
			return (allocateFailed());
	}
	return (noErrors());
}

void	freeFile(t_file **file)
{
	if (file == NULL || *file == NULL)
		return ;
	if ((*file)->name != NULL)
		free((*file)->name);
	if ((*file)->path != NULL)
		free((*file)->path);
	if ((*file)->symlink != NULL)
		free((*file)->symlink);
	free(*file);
	*file = NULL;
}

