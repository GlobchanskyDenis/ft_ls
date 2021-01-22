#include "ft_ls.h"

t_file	*newFile(char const *name, char const *path, int type)
{
	t_file	*dst;

	if (!(dst = (t_file *)ft_memalloc(sizeof(t_file))))
		return (NULL);
	dst->type = type;
	if (name == NULL)
		return (dst);
	if (!(dst->name = ft_strdup((char *)(name))))
	{
		freeFile(&dst);
		return NULL;
	}
	dst->path = (char *)path;
	return (dst);
}

void	insertAsChild(t_file *directory, t_file *newfile)
{
	t_file	*node;

	if (directory->child == NULL)
		directory->child = newfile;
	else
	{
		node = directory->child;
		while (node->next)
			node = node->next;
		node->next = newfile;
	}
}

void	insertAsNext(t_file *headFile, t_file *newfile)
{
	if (headFile->next == NULL)
		headFile->next = newfile;
	else
	{
		while (headFile->next)
			headFile = headFile->next;
		headFile->next = newfile;
	}
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
	// if ((*file)->author != NULL)
	// 	stringDel(&((*file)->author));
	// if ((*file)->group != NULL)
	// 	stringDel(&((*file)->group));
	free(*file);
	*file = NULL;
}
