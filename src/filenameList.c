#include "ft_ls.h"

t_error	*addToFilenameList(char *filename, t_list **fileList)
{
	t_list	*newFilenameNode;

	if (filename == NULL || fileList == NULL)
		return (newError("empty pointer in addFilenameList"));
	if ((newFilenameNode = ft_lstnew_fag(NULL, 0)) == NULL)
		return (newError("malloc returned NULL"));
	if ((newFilenameNode->content = ft_strdup(filename)) == NULL)
	{
		free(newFilenameNode);
		return (newError("malloc returned NULL"));
	}
	if (*fileList == NULL)
		*fileList = newFilenameNode;
	else
		ft_lstadd(fileList, newFilenameNode);
	return (NULL);
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
		if (toDelete->content != NULL)
			free(toDelete->content);
		free(toDelete);
	}
	*fileList = NULL;
	return (0);
}
