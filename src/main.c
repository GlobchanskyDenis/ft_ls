#include "ft_ls.h"

int	getWidthTerminal(int flags)
{
	struct winsize win;

	if (ioctl(1, TIOCGWINSZ, &win) < 0)
	{
		// fprint("Вывод в файл\n");
		flags = setFlagInColumn(flags);
		flags |= (1 << DISABLE_QUOTES);
	}
	// fprint("columns %d\n", win.ws_col);
	// fprint("rows %d\n", win.ws_row);
	// fprint("x pixel %d\n", win.ws_xpixel);
	// fprint("y pixel %d\n", win.ws_ypixel);

	return (flags);
}

/*
**	reader - обработка флагов, проверка существования файлов из аргументов
**	initializeFileTree - считывание файлов и папок вместе с lstat и прочим
**	displayFileTree - буфферизованный вывод накопленной информации
*/

int	main(int ac, char **av)
{
	int			flags;
	t_error		error;
	t_file		*fileTree;
	t_list		*filenames;

	filenames = NULL;
	error = reader(ac, av, &flags, &filenames);
	if (flags & (1 << FLAG_HELP))
	{
		printUsage();
		return (freeError(error) + freeFilenameList(&filenames));
	}
	if (error.wasSet)
		return (handleError(error) + freeFilenameList(&filenames));
	flags = getWidthTerminal(flags);
	// flags = handleFlags(flags);
	// DumpFlags(flags);
	// DumpFiles(filenames);
	error = initializeFileTree(flags, filenames, &fileTree);
	freeFilenameList(&filenames);
	if (error.wasSet)
		return (freeFileTree(&fileTree) + handleError(error));
	// DumpFileTree(0, fileTree);
	error = displayFileTree(flags, fileTree);
	if (error.wasSet)
		return (freeFileTree(&fileTree) + handleError(error));
	freeFileTree(&fileTree);
	return (0);
}
