#include "ft_ls.h"

/*
**	Fills buffer by file mode.
**	This function calls only in case flag -l.
**	In case flag --color, file mode will be in color.
*/

void	fillFileMode(int flags, t_string *buf, t_file *file)
{
	stringCat(buf, (flags & FLAG_COLOR) ? COLOR_MODE : "");
	stringCat(buf, (file->type == DIRECTORY) ? "d" : ((file->type == 
		SYMBOLIC) ? "l" : "-"));
	stringCat(buf, (file->stat.st_mode & (1 << 8)) ? "r" : "-");
	stringCat(buf, (file->stat.st_mode & (1 << 7)) ? "w" : "-");
	if (file->stat.st_mode & (1 << 11))
		stringCat(buf, (file->stat.st_mode & (1 << 6)) ? "s" : "S");
	else
		stringCat(buf, (file->stat.st_mode & (1 << 6)) ? "x" : "-");
	stringCat(buf, (file->stat.st_mode & (1 << 5)) ? "r" : "-");
	stringCat(buf, (file->stat.st_mode & (1 << 4)) ? "w" : "-");
	if (file->stat.st_mode & (1 << 10))
		stringCat(buf, (file->stat.st_mode & (1 << 3)) ? "s" : "S");
	else
		stringCat(buf, (file->stat.st_mode & (1 << 3)) ? "x" : "-");
	stringCat(buf, (file->stat.st_mode & (1 << 2)) ? "r" : "-");
	stringCat(buf, (file->stat.st_mode & (1 << 1)) ? "w" : "-");
	if (file->stat.st_mode & (1 << 9))
		stringCat(buf, (file->stat.st_mode & (1 << 0)) ? "t" : "T");
	else
		stringCat(buf, (file->stat.st_mode & (1 << 0)) ? "x" : "-");
	stringCat(buf, (flags & FLAG_COLOR) ? NO_COLOR : "");
	stringCat(buf, " ");
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
	char *printTime;

	stringCat(buf, " ");
	if (flags & FLAG_U)
		printTime = ctime(&(file->stat.st_atime));
	else
		printTime = ctime(&(file->stat.st_mtime));
	if (printTime == NULL)
		return newError("ctime", strerror(errno));
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
	if (!stringGrantSize(buf, 10 + ft_strlen(file->name) +
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
