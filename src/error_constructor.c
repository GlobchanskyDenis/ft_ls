#include "ft_ls.h"

t_error	*newError(char *newPanic)
{
	t_error *error;

	if ((error = (t_error *)ft_memalloc(sizeof(t_error))) == NULL)
		return (NULL);
	if ((error->panic = ft_strdup(newPanic)) == NULL)
	{
		free(error);
		return (NULL);
	}
	return (error);
}

t_error *accessFailed(char const *av)
{
	t_error *error;

	if ((error = (t_error *)ft_memalloc(sizeof(t_error))) == NULL)
		return (NULL);
	error->access = av;
	return (error);
}

t_error *invalidOption(char c)
{
	t_error *error;

	if ((error = (t_error *)ft_memalloc(sizeof(t_error))) == NULL)
		return (NULL);
	error->option = c;
	return (error);
}

t_error	*emptyError()
{
	t_error *error;

	if ((error = (t_error *)ft_memalloc(sizeof(t_error))) == NULL)
		return (NULL);
	return (error);
}

t_error *permissionError(char const *fileName)
{
	t_error *error;

	if ((error = (t_error *)ft_memalloc(sizeof(t_error))) == NULL)
		return (NULL);
	if ((error->permission = ft_strdup(fileName)) == NULL)
	{
		free(error);
		return (NULL);
	}
	return (error);
}
