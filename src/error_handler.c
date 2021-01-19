#include "ft_ls.h"

t_error noErrors()
{
	t_error error;

	ft_bzero(&error, sizeof(error));
	return(error);
}

int		freeError(t_error *error)
{
	if (error != NULL)
	{
		if (error->panic != NULL)
			free(error->panic);
		if (error->permission != NULL)
			free(error->permission);
		error->wasSet = 0;
	}
	return (0);
}

int		handleError(t_error *error)
{
	if (error == NULL)
		return (0);
	if (error->panic != NULL)
		fprint_fd(2, "\033[41;30mERROR\033[m\033[31m - %s\033[m\n",
			error->panic);
	else if (error->access != NULL)
		fprint_fd(2, "ls: cannot access '%s': No such file or directory\n",
			error->access);
	else if (error->option)
		fprint_fd(2, "ls: invalid option -- '%c'\n%s\n",
			error->option,
			"Try 'ls --help' for more information.");
	else if (error->permission != NULL)
		fprint_fd(2, "ls: cannot open directory '%s': Permission denied\n",
			error->permission);
	else if (error->wasSet)
		fprint_fd(2, "\033[41;30mERROR\033[m\033[31m - %s\033[m\n",
			"malloc returned NULL");
	return freeError(error);
}