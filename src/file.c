#include "ft_ls.h"

/*
**	Constructor and handlers for t_file file type
*/

t_file	*newFile(char const *name, char *fullpath, int type)
{
	t_file	*dst;
	size_t	nameLen;

	if (name == NULL && fullpath != NULL)
		ft_strdel(&fullpath);
	if (fullpath == NULL)
		return (NULL);
	if (!(dst = (t_file *)ft_memalloc(sizeof(t_file))))
		return (NULL);
	dst->type = type;
	nameLen = ft_strlen(name);
	if (!(dst->name = (char *)malloc(nameLen * 2 + 2)))
	{
		freeFile(&dst);
		return NULL;
	}
	ft_strcpy(dst->name, name);
	dst->alterName = &(dst->name[nameLen + 1]);
	dst->isNeedQuotes = initAlternateString(dst->alterName, dst->name);
	dst->fullpath = fullpath;
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

