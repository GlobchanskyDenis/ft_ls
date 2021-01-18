#include "ft_ls.h"

t_error *checkFlags(const char c)
{
	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
		return (NULL);
	if (c == 'u' || c == 'f' || c == 'g' || c == 'd')
		return (NULL);
	return (invalidOption(c));
}

t_error	*checkForLongFlag(char const *av)
{
	if (!ft_strcmp("--all", av))
		return (NULL);
	if (!ft_strcmp("--reverse", av))
		return (NULL);
	if (!ft_strcmp("--recursive", av))
		return (NULL);
	if (!ft_strcmp("--directory", av))
		return (NULL);
	if (!ft_strcmp("--color", av))
		return (NULL);
	if (!ft_strcmp("--help", av))
	{
		printUsage();
		return (emptyError());
	}
	return (accessFailed(av));
}

void	parseShortFlags(const char *av, int *flags)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (av[i] == 'l')
			*flags |= FLAG_L;
		else if (av[i] == 'R')
			*flags |=  FLAG_RR;
		else if (av[i] == 'a')
			*flags |=  FLAG_A;
		else if (av[i] == 'r')
			*flags |=  FLAG_R;
		else if (av[i] == 't')
			*flags |=  FLAG_T;
		else if (av[i] == 'u')
			*flags |=  FLAG_U;
		else if (av[i] == 'f')
			*flags |=  FLAG_F;
		else if (av[i] == 'g')
			*flags |=  FLAG_G;
		else if (av[i] == 'd')
			*flags |=  FLAG_D;
	}
}

void	parseLongFlag(const char *av, int *flags)
{
	if (!ft_strcmp("--all", av))
		*flags = *flags | FLAG_A;
	if (!ft_strcmp("--reverse", av))
		*flags = *flags | FLAG_R;
	if (!ft_strcmp("--recursive", av))
		*flags = *flags | FLAG_RR;
	if (!ft_strcmp("--directory", av))
		*flags = *flags	| FLAG_D;
	if (!ft_strcmp("--color", av))
		*flags = *flags | FLAG_COLOR;
}

/*
**	parsing one program argument for flags
*/
t_error	*parseFlags(const char *av, int *flags)
{
	t_error	*error;

	if ((error = checkForErrors(av)) != NULL)
		return (error);
	if (!ft_strncmp("--", av, 2))
		parseLongFlag(av, flags);
	else if (av[0] == '-')
		parseShortFlags(av, flags);
	return (NULL);
}
