#include "ft_ls.h"

/*	Инициализирует структурку файла из аргумента CLI занесенную
**	в стандартный односвязный список t_list и вставляет его в дерево
**	файлов
**	Флаг isArgument в составе файла указывает на то, что файл был
**	создан из аргумента CLI
**	Создает файл, считывает аттрибуты файла, если это папка - считывает
**	(возможно рекурсивно) ее содержимое и инициализирует альтернативное
**	имя файла в зависимости от флага для сортировки как в оригинальной
**	функции (это костыль)  */

// static 

static t_error	initFileFromCLIinsertToTree(int flags, t_list *filename, \
	t_file **fileTree)
{
	t_file	*newfile;
	t_error error;

	newfile = newFile(filename->content, ft_strdup(filename->content), UNKNOWN, flags);
	if (!newfile)
		return (allocateFailed());
	error = readHandleFileAttributes(newfile);
	if (error.wasSet)
		return (error);
	if (newfile->type == DIRECTORY)
	{
		if ((flags & (1 << FLAG_RR)) || !(flags & (1 << FLAG_D)))
		{
			error = readDirFiles(flags, newfile);
			if (error.wasSet)
				return (error);
		}
	}
	newfile->isArgument = 1;
	insertByFlags(flags, *fileTree, newfile);
	return (noErrors());
}

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
		error = initFileFromCLIinsertToTree(flags, files, fileTree);
		if (error.wasSet)
			return (error);
		files = files->next;
	}
	newfile = *fileTree;
	*fileTree = (*fileTree)->child;
	freeFile(&newfile);
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

	*fileTree = newFile(".", ft_strdup("."), DIRECTORY, flags);
	if (!(*fileTree))
		return (allocateFailed());
	if (files == NULL)
	{
		error = readHandleFileAttributes(*fileTree);
		if (error.wasSet)
			return (error);
		if (flags & (1 << FLAG_D))
			return (noErrors());
		error = readDirFiles(flags, *fileTree);
		if (error.wasSet)
			return (error);
		return (noErrors());
	}
	else
		return (initializeFromFileList(flags, files, fileTree));
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
