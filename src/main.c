#include "ft_ls.h"

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
	if (flags & FLAG_HELP)
	{
		printUsage();
		return (freeError(&error) + freeFilenameList(&filenames));
	}
	if (error.wasSet)
		return (handleError(&error) + freeFilenameList(&filenames));
	// DumpFlags(flags);
	error = initializeFileTree(flags, filenames, &fileTree);
	freeFilenameList(&filenames);
	if (error.wasSet)
		return (freeFileTree(&fileTree) + handleError(&error));
	error = displayFileTree(flags, fileTree);
	if (error.wasSet)
		return (freeFileTree(&fileTree) + handleError(&error));
	// DumpFileTree(0, fileTree);
	freeFileTree(&fileTree);
	return (0);
}
