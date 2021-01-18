#include "ft_ls.h"

int		amountFiles(t_file *fileTree)
{
	if (fileTree == NULL && fileTree != NULL)
		fprint("Заглушка\n"); /// чтобы успокоить werror
	return (2);
}

void	displayFiles(t_file *fileTree, int flags)
{
	int		i;
	flags = 0;  /// чтобы успокоить werror

	i = 0;
	while (i < amountFiles(fileTree))
	{
		fprint("FILE FLAG %d\n", flags);
		i++;
	}
}

int		main(int ac, char **av)
{
	int			flags;
	t_error		*error;
	t_file		*fileTree;
	t_list		*filenames;

	filenames = NULL;
	if ((error = reader(ac, av, &flags, &filenames)) != NULL)
		return (handleError(error) + freeFilenameList(&filenames));

	// DumpFlags(flags);
	// DumpFiles(files);

	if ((error = initializeFileTree(flags, &filenames, &fileTree)) != NULL)
	{
		freeFilenameList(&filenames);
		freeFileTree(&fileTree);
		return (handleError(error));
	}
	freeFilenameList(&filenames);
	DumpFileTree(0, fileTree);
	freeFileTree(&fileTree);
	// if (amountFiles(fileList) > 0)
	// displayFiles(fileList, flags);
	// freeFileList(fileList);
	return (0);
}
