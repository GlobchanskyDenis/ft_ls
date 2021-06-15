#include "ft_ls.h"

/*
**	In the case of specifying the mapping of the necessary files
**	and folders from the arguments - first we collect the file names
**	into a list t_list type
*/

t_error	addToFilenameList(char *filename, t_list **fileList)
{
	t_list	*newFilenameNode;
	t_list	*node;

	if (filename == NULL || fileList == NULL)
		return (newError("filename or fileList is NULL",
				"addFilenameList function"));
	newFilenameNode = ft_lstnew_fag(filename, 0);
	if (newFilenameNode == NULL)
		return (allocateFailed());
	if (*fileList == NULL)
		*fileList = newFilenameNode;
	else
	{
		node = *fileList;
		while (node->next)
			node = node->next;
		node->next = newFilenameNode;
	}
	return (noErrors());
}

int	freeFilenameList(t_list **fileList)
{
	t_list	*node;
	t_list	*toDelete;

	if (fileList == NULL)
		return (0);
	node = *fileList;
	while (node != NULL)
	{
		toDelete = node;
		node = node->next;
		free(toDelete);
	}
	*fileList = NULL;
	return (0);
}
