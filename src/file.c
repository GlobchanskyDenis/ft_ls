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
	if (!(dst->alterName = ft_strdup((char *)(name))))
	{
		freeFile(&dst);
		return NULL;
	}
	stringToUpCase(dst->alterName);
	dst->path = (char *)path;
	return (dst);
}

// void	insertAsChild(t_file *directory, t_file *newfile)
// {
// 	t_file	*node;

// 	if (directory->child == NULL)
// 		directory->child = newfile;
// 	else
// 	{
// 		node = directory->child;
// 		while (node->next)
// 			node = node->next;
// 		node->next = newfile;
// 	}
// }

void	insertAsNext(t_file *headFile, t_file *newfile)
{
	fprint("INSERT AS NEXT !!\n");
	if (headFile->next == NULL)
		headFile->next = newfile;
	else
	{
		while (headFile->next)
			headFile = headFile->next;
		headFile->next = newfile;
	}
}

void	insertFile(t_file *dir, t_file *newfile,
	int (*insert)(t_file *dir, t_file *prev, t_file *next, t_file *node))
{
	t_file *node;

	// fprint("\n\n------ INSERTING FILE %s ---------\n", newfile->name);
	// DumpFileTree(0, dir);

	if (dir->child == NULL)
		dir->child = newfile;
	else
	{
		node = dir->child;
		while (!(insert(dir, node, node->next, newfile)))
			node = node->next;
	}
	
	// fprint("------ INSERTING RESULTS ---------\n");
	// DumpFileTree(0, dir);
	// fprint("\n\n");
}

void	insertFileByFlags(int flags, t_file *dir, t_file *newfile)
{
	if (flags & FLAG_R)
		insertFile(dir, newfile, insertByNameReverse);
	else
		insertFile(dir, newfile, insertByName);
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
	if ((*file)->alterName != NULL)
		free((*file)->alterName);
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
