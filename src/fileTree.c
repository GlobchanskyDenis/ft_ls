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

t_error	initFileFromCLIinsertToTree(int flags, t_list *filename, \
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
		error = readDirFiles(flags, newfile);
		if (error.wasSet)
			return (error);
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
		newfile = newFile(files->content, ft_strdup(files->content), UNKNOWN, flags);
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
	newfile = *fileTree;
	*fileTree = (*fileTree)->child;
	freeFile(&newfile);
	return (noErrors());
}

/*
**	Если в аргументах не было указано имен файлов, то начинаю
**	формировать файловое дерево с текущей папки (.)
**	(.) -> считываются дочерние файлы и папки -> Если включен
**	флаг R - считываем рекурсивно
**	readDirFiles проверяет наличие рекурсии и осуществляет ее
*/

// static t_error	initializeFromCurrentDirectory(int flags, t_file **fileTree)
// {
// 	*fileTree = newFile(".", ft_strdup("."), DIRECTORY);
// 	if (!(*fileTree))
// 		return (allocateFailed());
// 	error = readHandleFileAttributes(*fileTree);
// 	if (error.wasSet)
// 		return (error);
// 	if (flags & (1 << FLAG_D))
// 		return (noErrors());
// 	error = readDirFiles(flags, *fileTree);
// 	if (error.wasSet)
// 		return (error);
// 	return (noErrors());
// }

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
