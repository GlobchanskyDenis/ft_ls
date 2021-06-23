#include "ft_ls.h"

int	isDirecoryHasRecursion(t_file *directory)
{
	t_file	*file;

	file = directory;
	while (file)
	{
		if (file->child != NULL)
		{
			return (1);
		}
		file = file->next;
	}
	return (0);
}
