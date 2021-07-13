#include "ft_ls.h"

/*	Разделяет файлы сепаратором (в зависимости от флага)
**	Если текущий файл был последним - сепаратор всегда - перенос строки  */

static t_error	fillBufFileSepatator(int flags, t_string *buf, t_file *nextFile)
{
	if (!stringGrantSize(buf, 3))
		return (allocateFailed());
	if (nextFile == NULL || (flags & (1 << FLAG_L)) || \
		(flags & (1 << FLAG_1)) || (flags & (1 << FLAG_G)))
		stringCat(buf, "\n");
	else
		stringCat(buf, "  ");
	return (noErrors());
}

/*	Выводит все имена файлов, которые содержатся в данной папке
**	разделяя их сепаратором в зависимости от комбинации флагов
**	и того, является ли файл последним в папке (перенос строки)
**	если файлов вообще не было - просто делает перенос строки  */

static t_error	fillBufFilenames(int flags, t_string *buf, t_file *head, \
	t_meta meta)
{
	t_file	*file;
	t_error	error;

	file = head;
	while (file)
	{
		error = fillBufFile(flags, buf, file, meta);
		if (error.wasSet)
			return (error);
		error = fillBufFileSepatator(flags, buf, file->next);
		if (error.wasSet)
			return (error);
		file = file->next;
	}
	return (noErrors());
}

/*	Данная функция вызывается только в случае включенного флага рекурсии
**	Проверка должна осуществляться в функции выше  */

static t_error	displayFoldersRecursively(int flags, t_string *buf, \
	t_file *head)
{
	t_file	*file;
	t_error	error;

	file = head;
	while (file)
	{
		if (file->type != DIRECTORY || !ft_strcmp(file->name, ".") || \
			!ft_strcmp(file->name, ".."))
		{
			file = file->next;
			continue ;
		}
		if ((calcOnlyNotDirectories(head) > 0 || (calcOnlyDirectories(head) > 1 \
			&& file != head)) && !stringCat(buf, "\n"))
			return (allocateFailed());
		error = fillBufDirFullpathTotal(flags, buf, file, calcOnlyDirectories(head));
		if (error.wasSet)
			return (error);
		error = fillBufRecurs(flags, buf, file->child, file->meta);
		if (error.wasSet)
			return (error);
		file = file->next;
	}
	return (noErrors());
}

/*
**	Рекурсивно заполняю буфер
*/

t_error	fillBufRecurs(int flags, t_string *buf, t_file *head, t_meta meta)
{
	t_error	error;

	error = fillBufFilenames(flags, buf, head, meta);
	if (error.wasSet)
		return (error);
	if (flags & (1 << FLAG_RR))
	{
		error = displayFoldersRecursively(flags, buf, head);
		if (error.wasSet)
			return (error);
	}
	return (noErrors());
}

/*	Это вариант отображения, когда список файлов для отображения
**	был задан аргументами файловой строки
**	Пока что начинка полностью повторяет fillBufRecurs (сделано
**	осознанно, так как в будущем функционал может начать отличаться)  */

t_error	displayCLIarguments(int flags, t_string *buf, t_file *head)
{
	t_error	error;
	t_file	*file;
	// int		filesWasPrinted;
	t_meta	commonFilesMeta;

	file = head;
	// filesWasPrinted = 0;
	commonFilesMeta = calcMetaOnlyFromFiles(head);
	while (file)
	{
		if (file->type != DIRECTORY)
		{
			error = fillBufFile(flags, buf, file, commonFilesMeta);
			if (error.wasSet)
				return (error);
			error = fillBufFileSepatator(flags, buf, file->next);
			if (error.wasSet)
				return (error);
			// filesWasPrinted = 1;
		}
		file = file->next;
	}
	error = displayFoldersRecursively(flags, buf, head);
	if (error.wasSet)
		return (error);
	return (noErrors());
}

t_error	displayCurrentFolder(int flags, t_string *buf, t_file *head)
{
	t_error	error;
	t_meta	commonFilesMeta;

	if (flags & (1 << FLAG_D))
	{
		commonFilesMeta = calcMetaOnlyFromFiles(head);
		error = fillBufRecurs(flags, buf, head, commonFilesMeta);
	}
	else
	{
		error = fillBufDirFullpathTotal(flags, buf, head, calcOnlyDirectories(head));
		if (error.wasSet)
			return (error);
		error = fillBufRecurs(flags, buf, head->child, head->meta);
		if (error.wasSet)
			return (error);
	}
	return (noErrors());
}

/*
**	Буфферизованный вывод накопленной информации в стандартный вывод
**	(через строку-вектор из libft)
**	Первое условие в цикле - фактически костыль, чтобы если папка
**	единственная - не выводить шапку
*/

t_error	displayFileTree(int flags, t_file *head)
{
	t_string	*buf;
	t_error		error;

	buf = stringNew(1000000);
	if (!buf)
		return (allocateFailed());
	if (flags & (1 << FLAG_FILE_ARGS))
		error = displayCLIarguments(flags, buf, head);
	else
		error = displayCurrentFolder(flags, buf, head);
	if (error.wasSet && stringDel(&buf))
		return (error);
	write(1, buf->str, buf->length);
	stringDel(&buf);
	return (noErrors());
}
