#include "ft_ls.h"

/*	Считается что в буффере достаточно места,
**	Проверка флагов должна проводится в функции выше  */

static void	fillBufDirFullpath(int flags, t_string *buf, t_file *dir)
{
	if (dir->isNeedPathQuotes && !(flags & (1 << DISABLE_QUOTES)))
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

t_error	fillBufDirFullpathTotal(int flags, t_string *buf, t_file *dir)
{
	if (!dir)
		return (noErrors());
	if (!stringGrantSize(buf, 50 + ft_strlen(dir->fullpath)))
		return (allocateFailed());
	if (flags & (1 << FLAG_RR))
		fillBufDirFullpath(flags, buf, dir);
	if (flags & (1 << SHOW_RIGHTS_GROUP_WEIGHT))
		fillBufDirTotal(buf, dir);
	return (noErrors());
}

static int	isCanPrintDirFullpath(int flags, t_file *dir, t_file *dirHead)
{
	int	amountDirs;
	// int	amountNormalDirs;
	// int	amountDamagedDirs;
	int	amountFiles;

	if (dir->accessErrno != 0)
		return (0);
	if (flags & (1 << FLAG_RR))
		return (1);
	amountDirs = calcOnlyDirectories(dirHead);
	// amountNormalDirs = calcOnlyDirectoriesThatWeCanAccess(dirHead);
	// amountDamagedDirs = amountDirs - amountNormalDirs;
	amountFiles = calcOnlyNotDirectories(dirHead);
	if (flags & (1 << FLAG_FILE_ARGS))
	{
		if (amountDirs > 1)
			return (1);
		if (amountFiles > 0)
			return (1);
	}
	return (0);
}

/*	dirHead - это head односвязного списка, в котором dir один из элементов
**	логика следующая. DirFullpath (в случае если папка была указана через CLI)
**	должен отображаться либо если есть рекурсия, либо если папка не одна
**	в списке и нет файлов, либо одна но есть также и файлы */

t_error fillBufDirFullpathTotalWithCLICondition(int flags, t_string *buf, \
	t_file *dir, t_file *dirHead)
{
	if (!dir)
		return (noErrors());
	if (!stringGrantSize(buf, 50 + ft_strlen(dir->fullpath)))
		return (allocateFailed());
	if (isCanPrintDirFullpath(flags, dir, dirHead))
		fillBufDirFullpath(flags, buf, dir);
	if ((flags & (1 << SHOW_RIGHTS_GROUP_WEIGHT)) && \
		dir->accessErrno == 0)
		fillBufDirTotal(buf, dir);
	return (noErrors());
}
