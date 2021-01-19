#include "ft_ls.h"

t_error	checkForErrors(char const *av)
{
	size_t	len;
	size_t	i;
	t_error error;

	if ((len = ft_strlen(av)) < 1)
		return (newError("Program arguments are invalid"));
	if (av[0] != '-' || (av[0] == '-' && len == 1))
		return (accessFailed(av));
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
*/
t_error	reader(int ac, char **av, int *flags, t_list **filenames)
{
	int		i;
	t_error error;

	if (ac < 0 || av == NULL)
		return (newError("Program arguments are invalid"));
	*flags = 0;
	*filenames = NULL;
	i = 1;
	while (i < ac)
	{
		error = parseFlags(av[i], flags);
		if (error.wasSet)
		{
			if ((isFileExist(av[i]) == 1))
			{
				addToFilenameList(av[i], filenames);
				freeError(&error);
			}
			else
				return (error);
		}
		i++;
	}
	return (noErrors());
}
