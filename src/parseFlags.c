#include "ft_ls.h"

/*	Этот блок просто не помещался в вызывающую функцию  */

static void	handleShortFlag(const char c, int *flags)
{
	if (c == 'l')
		*flags |= FLAG_L;
	else if (c == 'R')
		*flags |= FLAG_RR;
	else if (c == 'a')
		*flags |= FLAG_A;
	else if (c == 'r')
		*flags |= FLAG_R;
	else if (c == 't')
		*flags |= FLAG_T;
	else if (c == 'u')
		*flags |= FLAG_U;
	else if (c == 'f')
		*flags |= FLAG_F;
	else if (c == 'g')
		*flags |= FLAG_G;
	else if (c == 'd')
		*flags |= FLAG_D;
	else if (c == '1')
		*flags |= FLAG_1;
}

/*	По одному парсит все флаги из строки  */

static void	parseShortFlags(const char *av, int *flags)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		handleShortFlag(av[i], flags);
	}
}

/*	Парсит строку как длинный флаг  */

static void	parseLongFlag(const char *av, int *flags)
{
	if (!ft_strcmp("--all", av))
		*flags = *flags | FLAG_A;
	else if (!ft_strcmp("--reverse", av))
		*flags = *flags | FLAG_R;
	else if (!ft_strcmp("--recursive", av))
		*flags = *flags | FLAG_RR;
	else if (!ft_strcmp("--directory", av))
		*flags = *flags | FLAG_D;
	else if (!ft_strcmp("--color", av))
		*flags = *flags | FLAG_COLOR;
	else if (!ft_strcmp("--help", av))
		*flags = *flags | FLAG_HELP;
}

/*
**	Parsing one program argument for flags
*/

t_error	parseFlags(const char *av, int *flags)
{
	t_error	error;

	error = checkForErrors(av);
	if (error.wasSet)
		return (error);
	if (!ft_strncmp("--", av, 2))
		parseLongFlag(av, flags);
	else if (av[0] == '-')
		parseShortFlags(av, flags);
	return (noErrors());
}
