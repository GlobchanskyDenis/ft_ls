#include "ft_ls.h"

static t_error	parseLongFlagContinue(const char *av, int *flags)
{
	if (!ft_strcmp("--color", av))
	{
		*flags = *flags | (1 << FLAG_COLOR);
		return (noErrors());
	}
	else if (!ft_strcmp("--help", av))
	{
		*flags = *flags | (1 << FLAG_HELP);
		return (noErrors());
	}
	return (unrecognizedOption((char *)av));
}

/*	Парсит CLI аргумент как строку с длинным флагом  */

static t_error	parseLongFlag(const char *av, int *flags)
{
	if (!ft_strcmp("--all", av))
	{
		*flags = setFlagHiddenA(*flags);
		return (noErrors());
	}
	else if (!ft_strcmp("--reverse", av))
	{
		*flags = setFlagReverse(*flags);
		return (noErrors());
	}
	else if (!ft_strcmp("--recursive", av))
	{
		*flags = setFlagRecursion(*flags);
		return (noErrors());
	}
	else if (!ft_strcmp("--directory", av))
	{
		*flags = setFlagOnlyDirectories(*flags);
		return (noErrors());
	}
	return (parseLongFlagContinue(av, flags));
}

/*	Parsing one CLI argument for flags  */

t_error	parseCLIArgumentToFlags(const char *av, int *flags)
{
	if (!ft_strncmp("--", av, 2))
	{
		return parseLongFlag(av, flags);
	}
	else if (!ft_strncmp("-", av, 1))
	{
		return parseShortFlags(av, flags);
	}
	return (newError("Рефактор!!", \
		"parseCLIArgumentToFlags found imposible case!"));
}
