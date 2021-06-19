#include "ft_ls.h"

/*
**	Записывает в буффер все что касается данного файла
*/

static t_error	fillBufFile(int flags, t_string *buf, t_file *file, t_meta meta)
{
	t_error	error;

	if (flags & FLAG_L)
	{
		if (!stringGrantSize(buf, 50 + meta.sum))
			return (allocateFailed());
		fillBufFileMode(flags, buf, file, meta);
		stringItoaAlignR(buf, file->stat.st_nlink, meta.maxLinksNumLen, ' ');
		stringCat(buf, " ");
		fillFileAuthor(flags, buf, file, meta);
		stringItoaAlignR(buf, file->stat.st_size, meta.maxSizeLen, ' ');
		error = fillFileTime(flags, buf, file);
		if (error.wasSet)
			return (error);
		error = fillFileName(flags, buf, file);
		if (error.wasSet)
			return (error);
		// Отладка начало
		// if (!stringGrantSize(buf, 200))
		// 	return (allocateFailed());
		// stringCat(buf, "\t| ");
		// stringItoa(buf, file->stat.st_dev);
		// stringCat(buf, "\t| ");
		// stringItoa(buf, file->stat.st_rdev);
		// stringCat(buf, "\t| ");
		// stringItoa(buf, file->stat.st_rdev >> 8);
		// stringCat(buf, "\t| ");
		// stringItoa(buf, file->stat.st_rdev & 0b11111111);
		// stringCat(buf, " |");
		// Отладка конец
		stringCat(buf, "\n");
	}
	else 
	{
		error = fillFileName(flags, buf, file);
		if (error.wasSet)
			return (error);
	}
	return (noErrors());
}

static t_error	fillBufDirFullpath(int flags, t_string *buf, t_file *dir)
{
	if (!stringGrantSize(buf, 50 + ft_strlen(dir->fullpath)))
		return (allocateFailed());
	if (dir->isNeedQuotes)
		stringCat3(buf, "'", dir->fullpath, "'");
	else
		stringCat(buf, dir->fullpath);
	stringCat(buf, ":\n");
	if (flags & FLAG_L)
	{
		stringCat(buf, "total ");
		stringItoa(buf, dir->meta.blocksNum / 2);
		stringCat(buf, "\n");
	}
	return (noErrors());
}

/*
**	Рекурсивно заполняю буфер
*/

t_error	fillBufRecurs(int flags, t_string *buf, t_file *head, t_meta meta)
{
	t_file	*file;
	t_error	error;
	int		wasPrintedFirstFile;

	wasPrintedFirstFile = 0;
	file = head;
	/*	displaying only filenames in current folder  */
	while (file)
	{
		if (file->child != NULL && file->isArgument)
		{
			file = file->next;
			continue ;
		}
		if (wasPrintedFirstFile)
		{
			if (!(flags & FLAG_L) && !stringCat(buf, "  "))
				return (allocateFailed());
		}
		else
			wasPrintedFirstFile = 1;
		error = fillBufFile(flags, buf, file, meta);
		if (error.wasSet)
			return (error);
		file = file->next;
	}
	file = head;
	/*	displaing only folders  */
	while (file)
	{
		if (file->child == NULL)
		{
			file = file->next;
			continue ;
		}
		if (wasPrintedFirstFile)
		{
			if (!stringCat(buf, "\n\n"))
				return (allocateFailed());
		}
		else
			wasPrintedFirstFile = 1;
		error = fillBufDirFullpath(flags, buf, file);
		if (error.wasSet)
			return (error);
		error = fillBufRecurs(flags, buf, file->child, file->meta);
		if (error.wasSet)
			return (error);
		file = file->next;
	}
	return (noErrors());
}

t_error	displayLongFileTree(int flags, t_file *head)
{
	if (flags && !flags)
		head->name = NULL;
	return (noErrors());
}

/*
**	Нахожу мету головного файла и сам файл с которого рекурсивно начнется
**	печать информации в буффер
*/

t_meta	findMetaAndHead(int flags, t_file **head)
{
	t_file	*fileNode;
	t_meta	meta;

	fileNode = *head;
	meta = fileNode->meta;
	if ((flags & FLAG_FILE_ARGS || !(flags & FLAG_RR)) && fileNode->child)
	{
		meta = fileNode->meta;
		fileNode = fileNode->child;
		if (fileNode->next == NULL && fileNode->child != NULL)
		{
			meta = fileNode->meta;
			fileNode = fileNode->child;
		}
	}
	*head = fileNode;
	return (meta);
}

/*
**	Безопасно печатаю первую строку в буффер (количество блоков)
**	Количество блоков почему-то показывает вдвое большее оригинального
**	ls, поэтому делю на 2
*/

t_error	fillBufFirstLine(t_string *buf, t_meta meta)
{
	if (!stringCat(buf, "total "))
		return (allocateFailed());
	if (!stringItoa(buf, meta.blocksNum / 2))
		return (allocateFailed());
	if (!stringCat(buf, "\n"))
		return (allocateFailed());
	return (noErrors());
}

/*
**	Буфферизованный вывод накопленной информации в стандартный вывод
**	(через строку-вектор из libft)
*/

t_error	displayFileTree(int flags, t_file *head)
{
	t_string	*buf;
	t_error		error;
	t_meta		meta;

	buf = stringNew(1000000);
	if (!buf)
		return (allocateFailed());
	meta = findMetaAndHead(flags, &head);
	if (flags & FLAG_L)
	{
		error = fillBufFirstLine(buf, meta);
		if (error.wasSet && stringDel(&buf))
			return (allocateFailed());
	}
	error = fillBufRecurs(flags, buf, head, meta);
	if (error.wasSet && stringDel(&buf))
		return (error);
	if (!(flags & FLAG_L) && !stringCat(buf, "\n"))
		return (allocateFailed());
	write(1, buf->str, buf->length);
	stringDel(&buf);
	return (noErrors());
}
