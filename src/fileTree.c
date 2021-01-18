#include "ft_ls.h"

t_error	*initializeFileTree(int flags, t_list **files, t_file **fileTree)
{
	t_list	*node;
	t_file	*newfile;
	t_file	*toDelete;
	t_error	*error;

	*fileTree = NULL;
	if (*files == NULL)
	{
		if (!(*fileTree = newFile(NULL, NULL, 0, DIRECTORY)))
			return (newError("malloc returned NULL"));
		if ((flags & FLAG_D))
		{
			if (!((*fileTree)->name = ft_strdup(".")))
				return (newError("malloc returned NULL"));
			if (((flags & FLAG_L) || (flags & FLAG_G)) &&
				(error = readFileLstat(*fileTree)))
				return (error);
			return (NULL);
		}
		if ((error = readDirFiles(flags, *fileTree)))
			return (error);
		toDelete = *fileTree;
		*fileTree = (*fileTree)->child;
		freeFile(&toDelete);
		return (NULL);
	}
	else {
		while (*files)
		{
			node = *files;
			if (!(newfile = newFile((char *)(node->content), NULL, 0, UNKNOWN)))
				return (newError("malloc returned NULL"));
			*files = node->next;
			if (node->content != NULL)
				free(node->content);
			free(node);
			if (*fileTree == NULL)
				*fileTree = newfile;
			else
				insertAsNext(*fileTree, newfile);
		}
	}
	return (NULL);
}

void	freeFileTree(t_file **fileTree)
{
	t_file	*next;
	t_file	*child;

	if (fileTree == NULL || *fileTree == NULL)
		return ;
	next = (*fileTree)->next;
	child = (*fileTree)->child;
	freeFile(fileTree);
	freeFileTree(&next);
	freeFileTree(&child);
}