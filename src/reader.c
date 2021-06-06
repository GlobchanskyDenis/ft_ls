#include "ft_ls.h"

static t_error 	checkFlags(const char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (noErrors());
	if (c == 'u' || c == 'f' || c == 'g' || c == 'd' || c == '1')
		return (noErrors());
	return (invalidOption(c));
}

static t_error	checkForLongFlag(char const *av)
{
	if (!ft_strcmp("--all", av))
		return (noErrors());
	if (!ft_strcmp("--reverse", av))
		return (noErrors());
	if (!ft_strcmp("--recursive", av))
		return (noErrors());
	if (!ft_strcmp("--directory", av))
		return (noErrors());
	if (!ft_strcmp("--color", av))
		return (noErrors());
	if (!ft_strcmp("--help", av))
		return (noErrors());
	return (accessFailed(av, isFileNotExist(av)));
}

t_error	checkForErrors(char const *av)
{
	size_t	len;
	size_t	i;
	t_error error;

	if ((len = ft_strlen(av)) < 1)
		return (newError("Program arguments are invalid",
					"checkForErrors function"));
	if (av[0] != '-' || (av[0] == '-' && len == 1))
		return (accessFailed(av, isFileNotExist(av)));
	if ((ft_strncmp("--", av, 2) == 0) && len > 2)
		return (checkForLongFlag(av));
	i = 1;
	while (i < len)
	{
		error = checkFlags(av[i]);
		if (error.wasSet)
			return (error);
		i++;
	}
	return (noErrors());
}

void	printUsage()
{
	fprint("Usage: ft_ls [OPTION]... [FILE]...\nList information ");
	fprint("about the FILEs (the current directory by default).\n");
	fprint("\tMANDATORY\n");
	fprint("   -a, --all\t\tdo not ignore entries starting with .\n");
	fprint("   -l\t\t\tuse a long listing format\n");
	fprint("   -r, --reverse\treverse order while sorting\n");
	fprint("   -t\t\t\tsort by modification time, newest first\n");
	fprint("   -R, --recursive\tlist subdirectories recursively\n");
	fprint("\n\tBONUSES\n");
	fprint("   -u\t\t\tsort by, and show, access time\n");
	fprint("   -f\t\t\tdisable sorting\n");
	fprint("   -g\t\t\tlike -l, but do not list owner\n");
	fprint("   -d, --directory\tlist directories themselves, not their %s",
		"contents\n");
	fprint("       --color\t\tdisplay in color\n");
	fprint("       --help\t\tdisplay this information\n");
}

/*
**	main function for parsing flags
**	Парсит флаги. Если флаг незнаком - принимается как имя файла и пытается считать его lstat.
**	Если lstat читается - значит это файл, если нет - значит это ошибка
*/

t_error	reader(int ac, char **av, int *flags, t_list **filenames)
{
	int		i;
	t_error error;
	t_error toReturnError;

	*flags = 0;
	*filenames = NULL;
	i = 0;
	toReturnError = noErrors();
	while (++i < ac)
	{
		error = parseFlags(av[i], flags);
		if (error.wasSet)
		{
			if (!isFileNotExist(av[i]) && freeError(&error) &&
					(*flags |= FLAG_FILE_ARGS))
				addToFilenameList(av[i], filenames);
			else
			{
				if (!toReturnError.wasSet)
					toReturnError = error;
			}
		}
	}
	return (toReturnError);
}
