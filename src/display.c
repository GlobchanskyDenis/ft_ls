#include "ft_ls.h"

void	handleErrno(t_string *buf, t_file *file)
{
	if (buf->length > 0)
	{
		write(1, buf->str, buf->length);
		buf->length = 0;
		buf->str[0] = 0;
		buf->str[1] = 0;
	}
	if (file->type == DIRECTORY)
		fprint_fd(2, "ls: cannot open directory '%s': %s\n", file->name, \
			strerror(file->accessErrno));
	else
		fprint_fd(2, "ls: cannot access '%s': %s\n", file->name, \
			strerror(file->accessErrno));
}

/*	Разделяет файлы сепаратором (в зависимости от флага)
**	Если текущий файл был последним - сепаратор всегда - перенос строки  */

t_error	fillBufFileSepatator(int flags, t_string *buf, t_file *nextFile)
{
	if (!stringGrantSize(buf, 3))
		return (allocateFailed());
	if (nextFile == NULL || (flags & (1 << SEPARATOR_EOL)))
		stringCat(buf, "\n");
	else
		stringCat(buf, "   ");
	return (noErrors());
}

/*	Выводит все имена файлов, которые содержатся в данной папке
**	разделяя их сепаратором в зависимости от комбинации флагов
**	и того, является ли файл последним в папке (перенос строки)
**	если файлов вообще не было - просто делает перенос строки  */

t_error	fillBufFilenames(int flags, t_string *buf, t_file *head, \
	t_meta meta)
{
	t_file	*file;
	t_error	error;

	file = head;
	while (file)
	{
		if (file->accessErrno != 0)
			handleErrno(buf, file);
		else
		{
			error = fillBufFile(flags, buf, file, meta);
			if (error.wasSet)
				return (error);
			error = fillBufFileSepatator(flags, buf, file->next);
			if (error.wasSet)
				return (error);
		}
		file = file->next;
	}
	return (noErrors());
}

t_error	displayEOL(t_string *buf, t_file *head, t_file *file, \
	int *flags)
{
	if (file->accessErrno != 0)
		return (noErrors());
	if ((*flags) & (1 << SEPARATOR_FOLDERS_EOL))
	{
		if (!stringCat(buf, "\n"))
			return (allocateFailed());
	}
	else if ((file != head && (calcOnlyNotDirectories(head) > 0 || \
		calcOnlyDirectories(head) > 1)) || buf->length != 0)
	{
		if (!stringCat(buf, "\n"))
			return (allocateFailed());
		(*flags) |= (1 << SEPARATOR_FOLDERS_EOL);
	}
	return (noErrors());
}

/*	Данная функция вызывается только в случае включенного флага рекурсии
**	Проверка должна осуществляться в функции выше  */

t_error	displayFoldersRecursively(int flags, t_string *buf, \
	t_file *head)
{
	t_file	*file;
	t_error	error;

	file = head;
	while (file)
	{
		if (file->type != DIRECTORY || ((!ft_strcmp(file->name, ".") || \
			!ft_strcmp(file->name, "..")) && !file->isArgument))
		{
			file = file->next;
			continue ;
		}
		error = displayEOL(buf, head, file, &flags);
		if (error.wasSet)
			return (error);
		error = fillBufDirFullpathTotalWithCLICondition(flags, buf, file, head);
		if (error.wasSet)
			return (error);
		error = fillBufRecurs(flags, buf, file->child, file->meta);
		if (error.wasSet)
			return (error);
		file = file->next;
	}
	return (noErrors());
}
