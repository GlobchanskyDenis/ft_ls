#include "ft_ls.h"

t_error	initializeFileTree(int flags, t_list **files, t_file **fileTree)
{
	t_list	*node;
	t_file	*newfile;
	t_file	*toDelete;
	t_error	error;

	*fileTree = NULL;
	if (*files == NULL)
	{
		if (!(*fileTree = newFile(NULL, NULL, DIRECTORY)))
			return (allocateFailed());
		if ((flags & FLAG_D))
		{
			if (!((*fileTree)->name = ft_strdup(".")))
				return (allocateFailed());
			if ((flags & FLAG_L) || (flags & FLAG_G))
			{
				error = readFileLstat(*fileTree);
				if (error.wasSet)
					return (error);
			}
			return (noErrors());
		}
		error = readDirFiles(flags, *fileTree);
		if (error.wasSet)
			return (error);
		toDelete = *fileTree;
		*fileTree = (*fileTree)->child;
		freeFile(&toDelete);
		return (noErrors());
	}
	else {
		while (*files)
		{
			node = *files;
			if (!(newfile = newFile((char *)(node->content), NULL, UNKNOWN)))
				return (allocateFailed());
			*files = node->next;
			free(node);
			error = readFileLstat(newfile);
			if (error.wasSet)
				return (error);
			if (*fileTree == NULL)
				*fileTree = newfile;
			else
				insertToNextByFlags(flags, fileTree, newfile);
				// insertAsNext(*fileTree, newfile);
		}
	}
	return (noErrors());
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