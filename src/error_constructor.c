#include "ft_ls.h"

/*
**	Functions of this file creates different types of errors
*/

t_error	newError(char *cause, char *description)
{
	t_error	error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	error.panic = ft_concat3(cause, ": ", description);
	return (error);
}

t_error	accessFailed(char const *av, int errNo)
{
	t_error	error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	error.access = av;
	error.errNo = errNo;
	return (error);
}

t_error	invalidOption(char c)
{
	t_error	error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	error.option = c;
	return (error);
}

t_error	unrecognizedOption(char *argument)
{
	t_error	error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	error.panic = ft_concat3("ls: unrecognized option '", \
		argument, "'");
	return (error);
}

t_error	allocateFailed(void)
{
	t_error	error;

	ft_bzero(&error, sizeof(error));
	error.wasSet = 1;
	return (error);
}
