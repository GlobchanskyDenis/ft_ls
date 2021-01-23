#include "ft_ls.h"

t_error	addToFilenameList(char *filename, t_list **fileList)
{
	t_list	*newFilenameNode;

	if (filename == NULL || fileList == NULL)
		return (newError("filename or fileList is NULL", "addFilenameList function"));
	if ((newFilenameNode = ft_lstnew_fag(filename, 0)) == NULL)
		return (allocateFailed());
	if (*fileList == NULL)
		*fileList = newFilenameNode;
	else
		ft_lstadd(fileList, newFilenameNode);
	return (noErrors());
}

int		freeFilenameList(t_list **fileList)
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
