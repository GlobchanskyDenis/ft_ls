#include "ft_ls.h"

static t_error	handleShortFlagContinue2(const char c, int *flags)
{
	if (c == 'd')
	{
		*flags = setFlagOnlyDirectories(*flags);
		return (noErrors());
	}
	else if (c == '1')
	{
		*flags = setFlagInColumn(*flags);
		return (noErrors());
	}
	return (invalidOption(c));
}

static t_error	handleShortFlagContinue1(const char c, int *flags)
{
	if (c == 't')
	{
		*flags= setFlagSortByModificationTime(*flags);
		return (noErrors());
	}
	else if (c == 'u')
	{
		*flags = setFlagSortByAccessTime(*flags);
		return (noErrors());
	}
	else if (c == 'f')
	{
		*flags = setFlagDisableSort(*flags);
		return (noErrors());
	}
	else if (c == 'g')
	{
		*flags = setFlagLongWithoutAuthor(*flags);
		return (noErrors());
	}
	return (handleShortFlagContinue2(c, flags));
}

/*	Ищет наличие флага по одной букве (короткий флаг)  */

static t_error	handleShortFlag(const char c, int *flags)
{
	if (c == 'l')
	{
		*flags = setFlagLong(*flags);
		return (noErrors());
	}
	else if (c == 'R')
	{
		*flags = setFlagRecursion(*flags);
		return (noErrors());
	}
	else if (c == 'a')
	{
		*flags = setFlagHiddenA(*flags);
		return (noErrors());
	}
	else if (c == 'r')
	{
		*flags = setFlagReverse(*flags);
		return (noErrors());
	}
	return (handleShortFlagContinue1(c, flags));
}

/*	Парсит CLI аргумент как строку с короткими флагами  */

t_error	parseShortFlags(const char *av, int *flags)
{
	int		i;
	t_error	error;

	i = 0;
	while (av[++i])
	{
		error = handleShortFlag(av[i], flags);
		if (error.wasSet)
			return (error);
	}
	return (noErrors());
}
