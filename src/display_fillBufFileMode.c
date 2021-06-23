#include "ft_ls.h"

static void	fillBufEndFileMode(int flags, t_string *buf, t_file *file, \
	t_meta meta)
{
	if (file->hasACL)
		stringCat(buf, "+");
	else if (meta.hasACL)
		stringCat(buf, " ");
	if (flags & (1 << FLAG_COLOR))
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
