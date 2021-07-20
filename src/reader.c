#include "ft_ls.h"

void	printUsage(void)
{
	fprint("Usage: ft_ls [OPTION]... [FILE]...\nList information ");
	fprint("about the FILEs (the current directory by default).\n");
	fprint("\tMANDATORY\n");
	fprint("   -a, --all\t\tdo not ignore entries starting with .\n");
	fprint("   -l\t\t\tuse a long listing format\n");
	fprint("   -r, --reverse\treverse order while sorting\n");
	fprint("   -t\t\t\tsort by modification time, newest first\n");
	fprint("   -R, --recursive\tlist subdirectories recursively\n");
	fprint("   -1\t\t\tlist one file per line\n");
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
**	Парсит флаги. Если флаг незнаком - принимается как имя файла и пытается
**	считать его lstat. Если lstat читается - значит это файл, если нет -
**	значит это ошибка
*/

t_error	reader(int ac, char **av, int *flags, t_list **filenames)
{
	int		i;
	t_error	error;

	*flags = setSortByName(0) | (1 << SHOW_MODIF_TIME);
	*filenames = NULL;
	i = 0;
	while (++i < ac)
	{
		if (isFlag(av[i]))
		{
			error = parseCLIArgumentToFlags(av[i], flags);
			if (error.wasSet)
				return (error);
		}
		else if (isNeedToSkipThisFlag(av[i]))
			continue ;
		else
		{
			*flags = *flags | (1 << FLAG_FILE_ARGS);
			addToFilenameList(av[i], filenames);
		}
	}
	return (noErrors());
}
