#include "ft_ls.h"

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

	error = fillBufDirFullpathTotal(flags, buf, head);
	if (error.wasSet)
		return (error);
	error = fillBufRecurs(flags, buf, head->child, head->meta);
	if (error.wasSet)
		return (error);
	return (noErrors());
}

t_error	displayFolderWithFlagD(int flags, t_string *buf, \
	t_file *head)
{
	t_file	*file;
	t_error	error;
	t_meta	commonFilesMeta;

	commonFilesMeta = calcMetaOnlyFromFiles(head);
	file = head;
	while (file)
	{
		error = fillBufFile(flags, buf, file, commonFilesMeta);
		if (error.wasSet)
			return (error);
		if (!stringCat(buf, "\n"))
			return (allocateFailed());
		file = file->next;
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
	if (flags & (1 << FLAG_D))
		error = displayFolderWithFlagD(flags, buf, head);
	else if (flags & (1 << FLAG_FILE_ARGS))
		error = displayCLIarguments(flags, buf, head);
	else
		error = displayCurrentFolder(flags, buf, head);
	if (error.wasSet && stringDel(&buf))
		return (error);
	write(1, buf->str, buf->length);
	stringDel(&buf);
	return (noErrors());
}
