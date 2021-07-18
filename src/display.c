#include "ft_ls.h"

static void	handleErrno(t_string *buf, t_file *file)
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

static t_error	fillBufFileSepatator(int flags, t_string *buf, t_file *nextFile)
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

static t_error	fillBufFilenames(int flags, t_string *buf, t_file *head, \
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

static t_error	displayEOL(t_string *buf, t_file *head, t_file *file, \
	int *flags)
{
	if (file->accessErrno != 0)
		return (noErrors());
	if ((*flags) & (1 << SEPARATOR_FOLDERS_EOL))
	{
		if (!stringCat(buf, "\n"))
			return (allocateFailed());
	}
	else if (file != head && (calcOnlyNotDirectories(head) > 0 || \
		calcOnlyDirectories(head) > 1))
	{
		if (!stringCat(buf, "\n"))
			return (allocateFailed());
		(*flags) |= (1 << SEPARATOR_FOLDERS_EOL);
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

/*	Рекурсивно заполняю буфер
**	0 последним аргументом говорит о том, что первый EOL
**	ставить по своему усмотрению  */

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
	t_meta	commonFilesMeta;

	file = head;
	commonFilesMeta = calcMetaOnlyFromFiles(head);
	while (file)
	{
		if (file->accessErrno != 0)
			handleErrno(buf, file);
		else if (file->type != DIRECTORY)
		{
			error = fillBufFile(flags, buf, file, commonFilesMeta);
			if (error.wasSet)
				return (error);
			error = fillBufFileSepatator(flags, buf, file->next);
			if (error.wasSet)
				return (error);
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
		if (error.wasSet)
			return (error);
	}
	else
	{
		error = fillBufDirFullpathTotal(flags, buf, head);
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

	buf = stringNew(START_BUF_SIZE);
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
