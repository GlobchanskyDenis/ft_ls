#include "ft_ls.h"

/*	Считается что в буффере достаточно места,
**	Проверка флагов должна проводится в функции выше  */

static void	fillBufDirFullpath(t_string *buf, t_file *dir)
{
	if (dir->isNeedQuotes)
		stringCat3(buf, "'", dir->fullpath, "'");
	else
		stringCat(buf, dir->fullpath);
	stringCat(buf, ":\n");
}

/*	Считается что в буффере достаточно места,
**	Проверка флага L должна проводится в функции выше  */

static void	fillBufDirTotal(t_string *buf, t_file *dir)
{
	stringCat(buf, "total ");
	stringSizeTtoa(buf, dir->meta.blocksNum / 2);
	stringCat(buf, "\n");
}

/*
**	Если есть рекурсия (ориентируется не на флаг а на фактически присутствующие
**	файлы в подпапках) - выводит в буффер первую строку - имя папки с двоеточием
*/

t_error	fillBufDirFullpathTotal(int flags, t_string *buf, t_file *head, int amountOfDirectories)
{
	if (!head)
		return (noErrors());
	if (!stringGrantSize(buf, 50 + ft_strlen(head->fullpath)))
		return (allocateFailed());
	if ((flags & (1 << FLAG_RR)) || ((flags & (1 << FLAG_FILE_ARGS)) && \
		amountOfDirectories > 1))
		fillBufDirFullpath(buf, head);
	if ((flags & (1 << FLAG_L)) || (flags & (1 << FLAG_G)))
		fillBufDirTotal(buf, head);
	return (noErrors());
}
