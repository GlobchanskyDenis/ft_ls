#include "ft_ls.h"

/*
**	В случае включенного файла COLOR добавляет цвет
**	Заполняет буффер первым символом fileMode (тут сложная логика)
*/

static void	fillBufStartFileMode(int flags, t_string *buf, t_file *file)
{
	if (flags & FLAG_COLOR)
		stringCat(buf, COLOR_MODE);
	if (file->type == DIRECTORY)
		stringCat(buf, "d");
	else if (file->type == SYMBOLIC)
		stringCat(buf, "l");
	else if (!ft_strncmp(file->fullpath, "/dev", 4))
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

static void	fillBufEndFileMode(int flags, t_string *buf, t_file *file, \
	t_meta meta)
{
	if (file->hasACL)
		stringCat(buf, "+");
	else if (meta.hasACL)
		stringCat(buf, " ");
	if (flags & FLAG_COLOR)
		stringCat(buf, NO_COLOR);
	stringCat(buf, " ");
}

/*
**	Заполняет буффер символами 2, 3, 4 аттрибутов файла 
*/

static void	fillBufMiddle1FileMode(t_string *buf, t_file *file)
{
	if (file->stat.st_mode & (1 << 8))
		stringCat(buf, "r");
	else
		stringCat(buf, "-");
	if (file->stat.st_mode & (1 << 7))
		stringCat(buf, "w");
	else
		stringCat(buf, "-");
	if (file->stat.st_mode & (1 << 11))
	{
		if (file->stat.st_mode & (1 << 6))
			stringCat(buf, "s");
		else
			stringCat(buf, "S");
	}
	else
	{
		if (file->stat.st_mode & (1 << 6))
			stringCat(buf, "x");
		else
			stringCat(buf, "-");
	}
}

/*
**	Заполняет буффер символами 5, 6, 7 аттрибутов файла 
*/

static void	fillBufMiddle2FileMode(t_string *buf, t_file *file)
{
	if (file->stat.st_mode & (1 << 5))
		stringCat(buf, "r");
	else
		stringCat(buf, "-");
	if (file->stat.st_mode & (1 << 4))
		stringCat(buf, "w");
	else
		stringCat(buf, "-");
	if (file->stat.st_mode & (1 << 10))
	{
		if (file->stat.st_mode & (1 << 3))
			stringCat(buf, "s");
		else
			stringCat(buf, "S");
	}
	else
	{
		if (file->stat.st_mode & (1 << 3))
			stringCat(buf, "x");
		else
			stringCat(buf, "-");
	}
}

/*
**	Заполняет буффер символами 8, 9, 10 аттрибутов файла 
*/

static void	fillBufMiddle3FileMode(t_string *buf, t_file *file)
{
	if (file->stat.st_mode & (1 << 2))
		stringCat(buf, "r");
	else
		stringCat(buf, "-");
	if (file->stat.st_mode & (1 << 1))
		stringCat(buf, "w");
	else
		stringCat(buf, "-");
	if (file->stat.st_mode & (1 << 9))
	{
		if (file->stat.st_mode & (1 << 0))
			stringCat(buf, "t");
		else
			stringCat(buf, "T");
	}
	else
	{
		if (file->stat.st_mode & (1 << 0))
			stringCat(buf, "x");
		else
			stringCat(buf, "-");
	}
}

/*
**	Fills buffer by file mode.
**	This function calls only in case flag -l.
**	In case flag --color, file mode will be in color.
*/

void	fillBufFileMode(int flags, t_string *buf, t_file *file, t_meta meta)
{
	fillBufStartFileMode(flags, buf, file);
	fillBufMiddle1FileMode(buf, file);
	fillBufMiddle2FileMode(buf, file);
	fillBufMiddle3FileMode(buf, file);
	fillBufEndFileMode(flags, buf, file, meta);
}

void	fillFileAuthor(int flags, t_string *buf, t_file *file,
	t_meta meta)
{
	if (flags & FLAG_G)
		return ;
	if (flags & FLAG_COLOR)
		stringCat(buf, COLOR_AUTHOR);
	stringCatAlignL(buf, file->author, meta.maxAuthorLen, ' ');
	stringCat(buf, " ");
	stringCatAlignL(buf, file->group, meta.maxGroupLen, ' ');
	if (flags & FLAG_COLOR)
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
	if (flags & FLAG_U)
		printTime = ctime(&(file->stat.st_atime));
	else
		printTime = ctime(&(file->stat.st_mtime));
	if (printTime == NULL)
		return (newError("ctime", strerror(errno)));
	printTime = &(printTime[4]);
	stringCatN(buf, printTime, 12);
	stringCat(buf, " ");
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
	if (flags & FLAG_COLOR)
		stringCat(buf, COLOR_NAME);
	if (file->isNeedQuotes)
		stringCat(buf, "'");
	stringCat(buf, file->name);
	if (file->isNeedQuotes)
		stringCat(buf, "'");
	if (flags & FLAG_COLOR)
		stringCat(buf, NO_COLOR);
	if ((flags & FLAG_L) && file->type == SYMBOLIC)
		stringCat2(buf, " -> ", file->symlink);
	return (noErrors());
}
