#include "ft_ls.h"

t_error	newError(char *newPanic)
{
	t_error error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	error.panic = ft_strdup(newPanic);
	return (error);
}

t_error accessFailed(char const *av)
{
	t_error error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	error.access = av;
	return (error);
}

t_error invalidOption(char c)
{
	t_error error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	error.option = c;
	return (error);
}

t_error noErrors()
{
	t_error error;

	ft_bzero(&error, sizeof(error));
	return(error);
}

t_error	allocateFailed()
{
	t_error error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	return(error);
}
