#include "ft_ls.h"

/*
**	В случае включенного файла COLOR добавляет цвет
**	Заполняет буффер первым символом fileMode (тут сложная логика)
*/

void	fillBufStartFileMode(int flags, t_string *buf, t_file *file)
{
	if (flags & (1 << FLAG_COLOR))
		stringCat(buf, COLOR_MODE);
	if (file->type == DIRECTORY)
		stringCat(buf, "d");
	else if (file->type == SYMBOLIC)
		stringCat(buf, "l");
	else if (file->stat.st_rdev != 0 && file->stat.st_size == 0)
	{
		if (file->type == SOCKET)
			stringCat(buf, "c");
		else if (file->type == BLOCK_DEV)
			stringCat(buf, "b");
		else
			stringCat(buf, "-");
	}
	else
		stringCat(buf, "-");
}

void	fillFileAuthor(int flags, t_string *buf, t_file *file,
	t_meta meta)
{
	if (flags & (1 << FLAG_COLOR))
		stringCat(buf, COLOR_AUTHOR);
	stringCatAlignL(buf, file->author, meta.maxAuthorLen, ' ');
	stringCat(buf, " ");
	if (flags & (1 << FLAG_G))
		return ;
	stringCatAlignL(buf, file->group, meta.maxGroupLen, ' ');
	if (flags & (1 << FLAG_COLOR))
		stringCat(buf, NO_COLOR);
	stringCat(buf, " ");
}

/*
**	Fills buffer by file time.
**	This function calls only in case flag -l.
**	In case flag -u shows access time instead mod time
*/

t_error	fillFileTime(int flags, t_string *buf, t_file *file)
{
	char	*printTime;

	stringCat(buf, " ");
	if (flags & (1 << SHOW_ACCESS_TIME))
		printTime = ctime(&(file->stat.st_atime));
	else if (flags & (1 << SHOW_MODIF_TIME))
		printTime = ctime(&(file->stat.st_mtime));
	else
		printTime = ctime(&(file->stat.st_mtime));
	if (printTime == NULL)
		return (newError("(a/m)time", strerror(errno)));
	printTime = &(printTime[4]);
	stringCatN(buf, printTime, 12);
	stringCat(buf, " ");

	// printTime = ctime(&(file->stat.st_atime));
	// if (printTime == NULL)
	// 	return (newError("(a/m)time", strerror(errno)));
	// printTime = &(printTime[4]);
	// stringCatN(buf, printTime, 12);
	// stringCat(buf, " ");

	return (noErrors());
}

/*
**	Fills buffer by file name.
**	In case flag -l it also fills buffer by symlink name if it exist
**	In case flag --color id displays name in color
**	РЕФАКТОР!! ПЕРЕДАТЬ СЮДА МЕТУ И В ЗАВИСИМОСТИ ЕСЛИ ХОТЬ ОДИН ФАЙЛ В ПАПКЕ
**	ВЫВОДИТСЯ В АПОСТРОФАХ - все  
*/

t_error	fillFileName(int flags, t_string *buf, t_file *file)
{
	if (!stringGrantSize(buf, 10 + ft_strlen(file->name) + \
		safe_strlen(file->symlink)))
		return (allocateFailed());
	if (flags & (1 << FLAG_COLOR))
		stringCat(buf, COLOR_NAME);
	if (file->isNeedQuotes)
		stringCat(buf, "'");
	stringCat(buf, file->name);
	if (file->isNeedQuotes)
		stringCat(buf, "'");
	if (flags & (1 << FLAG_COLOR))
		stringCat(buf, NO_COLOR);
	if (((flags & (1 << FLAG_L)) || (flags & (1 << FLAG_G))) \
		&& file->type == SYMBOLIC)
		stringCat2(buf, " -> ", file->symlink);
	
	// if (ft_strlen(file->name) <= 7)
	// 	stringCat(buf, "\t");
	// if (ft_strlen(file->name) <= 15)
	// 	stringCat(buf, "\t");

	// stringCat2(buf, "\t", file->alterName);
	// stringCat(buf, "\t");
	// if (ft_strlen(file->name) <= 7)
	// 	stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_mtime);

	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_atime);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_atime / 60);

	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_dev);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_ino);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_mode);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_ctime);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_nlink);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_uid);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_gid);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_rdev);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_size);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_blksize);
	// stringCat(buf, "\t");
	// stringSizeTtoa(buf, file->stat.st_blocks);


	return (noErrors());
}

/*
**	Записывает в буффер все что касается данного файла
*/

t_error	fillBufFile(int flags, t_string *buf, t_file *file, t_meta meta)
{
	t_error	error;

	if (flags & (1 << FLAG_L) || flags & (1 << FLAG_G))
	{
		if (!stringGrantSize(buf, 50 + meta.sum))
			return (allocateFailed());
		fillBufFileMode(flags, buf, file, meta);
		stringSizeTtoaAlignR(buf, file->stat.st_nlink, meta.maxLinksNumLen, ' ');
		stringCat(buf, " ");
		fillFileAuthor(flags, buf, file, meta);
		fillBufByFileSizeColumn(buf, file, meta);
		error = fillFileTime(flags, buf, file);
		if (error.wasSet)
			return (error);
		error = fillFileName(flags, buf, file);
		if (error.wasSet)
			return (error);
	}
	else
	{
		error = fillFileName(flags, buf, file);
		if (error.wasSet)
			return (error);
	}
	return (noErrors());
}
