#include "ft_ls.h"

/*
**	Constructor and destructor for fileTree of t_file file type
*/

static t_error	initializeFromFileList(int flags, t_list *files,
		t_file **fileTree)
{
	t_file	*newfile;
	t_error	error;

	while (files)
	{
		newfile = newFile(files->content, ft_strdup(files->content), UNKNOWN);
		if (!newfile)
			return (allocateFailed());
		files = files->next;
		error = readHandleFileAttributes(newfile);
		if (error.wasSet)
			return (error);
		if (newfile->type == DIRECTORY)
		{
			error = readDirFiles(flags, newfile);
			if (error.wasSet)
				return (error);
		}
		newfile->isArgument = 1;
		insertByFlags(flags, *fileTree, newfile);
	}
	return (noErrors());
}

/*
**	Рекурсионное (в случае флага l) считывание файлов и папок
**	Зависит от считанных флагов, а также от того, были ли аргументом
**	заданы интересующие нас файлы
*/

t_error	initializeFileTree(int flags, t_list *files, t_file **fileTree)
{
	t_error	error;

	*fileTree = newFile(".", ft_strdup("."), DIRECTORY);
	if (!(*fileTree))
		return (allocateFailed());
	if (files == NULL)
	{
		error = readHandleFileAttributes(*fileTree);
		if (error.wasSet)
			return (error);
		if ((flags & FLAG_D))
			return (noErrors());
		error = readDirFiles(flags, *fileTree);
		if (error.wasSet)
			return (error);
		return (noErrors());
	}
	else
		initializeFromFileList(flags, files, fileTree);
	return (noErrors());
}

int	freeFileTree(t_file **fileTree)
{
	t_file	*next;
	t_file	*child;

	if (fileTree == NULL || *fileTree == NULL)
		return (0);
	next = (*fileTree)->next;
	child = (*fileTree)->child;
	freeFile(fileTree);
	freeFileTree(&next);
	freeFileTree(&child);
	return (1);
}
