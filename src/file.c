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

// void	insertAsNext(t_file *headFile, t_file *newfile)
// {
// 	fprint("INSERT AS NEXT !!\n");
// 	if (headFile->next == NULL)
// 		headFile->next = newfile;
// 	else
// 	{
// 		while (headFile->next)
// 			headFile = headFile->next;
// 		headFile->next = newfile;
// 	}
// }

void	insertToNext(t_file **head, t_file *newfile,
	int (*insert)(t_file **prev, t_file *next, t_file *node))
{
	t_file *node;

	if (insert(head, (*head)->next, newfile))
		return ;
	else
	{
		node = *head;
		while (!(insert(&node, node->next, newfile)))
			node = node->next;
	}
}

void	insertToChilds(t_file *dir, t_file *newfile,
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

void	insertToNextByFlags(int flags, t_file **head, t_file *newfile)
{
	if (flags & FLAG_R)
		insertToNext(head, newfile, insertNextByNameReverse);
	else
		insertToNext(head, newfile, insertNextByName);
}

void	insertToChildsByFlags(int flags, t_file *dir, t_file *newfile)
{
	if (flags & FLAG_R)
		insertToChilds(dir, newfile, insertByNameReverse);
	else
		insertToChilds(dir, newfile, insertByName);
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
	// if ((*file)->alterName != NULL)
	// 	free((*file)->alterName);
	if ((*file)->path != NULL)
		free((*file)->path);
	if ((*file)->symlink != NULL)
		free((*file)->symlink);
	free(*file);
	*file = NULL;
}
