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
	if (flags & (1 << FLAG_G))
		return ;
	if (flags & (1 << FLAG_COLOR))
		stringCat(buf, COLOR_AUTHOR);
	stringCatAlignL(buf, file->author, meta.maxAuthorLen, ' ');
	stringCat(buf, " ");
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
	if (flags & (1 << FLAG_U))
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
	if (flags & (1 << FLAG_COLOR))
		stringCat(buf, COLOR_NAME);
	if (file->isNeedQuotes)
		stringCat(buf, "'");
	stringCat(buf, file->name);
	if (file->isNeedQuotes)
		stringCat(buf, "'");
	if (flags & (1 << FLAG_COLOR))
		stringCat(buf, NO_COLOR);
	if ((flags & (1 << FLAG_L)) && file->type == SYMBOLIC)
		stringCat2(buf, " -> ", file->symlink);
	return (noErrors());
}
