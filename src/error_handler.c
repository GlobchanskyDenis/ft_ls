#include "ft_ls.h"

/*
**	Functions of this file handles errors
*/

int	freeError(t_error error)
{
	if (error.panic != NULL)
		free(error.panic);
	return (1);
}

int	handleError(t_error error)
{
	if (error.panic != NULL)
		fprint_fd(2, "\033[41;30mERROR\033[m\033[31m - %s\033[m\n",
			error.panic);
	else if (error.access != NULL)
		fprint_fd(2, "ls: cannot access '%s': %s\n",
			error.access, strerror(error.errNo));
	else if (error.option)
		fprint_fd(2, "ls: invalid option -- '%c'\n%s\n",
			error.option,
			"Try 'ls --help' for more information.");
	else if (error.wasSet)
		fprint_fd(2, "\033[41;30mERROR\033[m\033[31m - %s\033[m\n",
			"malloc returned NULL");
	return (freeError(error));
}

t_error	noErrors(void)
{
	t_error	error;

	ft_bzero(&error, sizeof(error));
	return (error);
}
