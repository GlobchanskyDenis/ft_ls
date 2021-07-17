#include "ft_ls.h"

// static t_error	checkFlags(const char c)
// {
// 	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
// 		return (noErrors());
// 	if (c == 'u' || c == 'f' || c == 'g' || c == 'd' || c == '1')
// 		return (noErrors());
// 	return (invalidOption(c));
// }

// static int	isShortFlagChar(const char c)
// {
// 	if (c == 'l' || c == 'R' || c == 'a' || c == 'r' || c == 't')
// 		return (1);
// 	if (c == 'u' || c == 'f' || c == 'g' || c == 'd' || c == '1')
// 		return (1);
// 	return (0);
// }

// static t_error	checkForLongFlag(char const *av)
// {
// 	if (!ft_strcmp("--all", av))
// 		return (noErrors());
// 	if (!ft_strcmp("--reverse", av))
// 		return (noErrors());
// 	if (!ft_strcmp("--recursive", av))
// 		return (noErrors());
// 	if (!ft_strcmp("--directory", av))
// 		return (noErrors());
// 	if (!ft_strcmp("--color", av))
// 		return (noErrors());
// 	if (!ft_strcmp("--help", av))
// 		return (noErrors());
// 	return (unrecognizedOption(av));
// }

// t_error	checkArgumentForFlagErrors(char const *av)
// {
// 	size_t	len;
// 	size_t	i;

// 	len = ft_strlen(av);
// 	if (ft_strncmp("--", av, 2) == 0)
// 		return (checkForLongFlag(av));
// 	else if (ft_strncmp("-", av, 1) == 0)
// 	{
// 		i = 1;
// 		while (i < len)
// 		{
// 			if (isShortFlagChar(av[i]))
// 				return (invalidOption(av[i]));
// 			i++;
// 		}
// 		return (noErrors());
// 	}
// 	return ();
// }

// static int	isShortFlag(char const *av, size_t length)
// {
// 	size_t	i;

// 	i = 1;
// 	while (i < length)
// 	{
// 		if (isShortFlagChar(av[i]) == 0)
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// static int	isLongFlag(char const *av)
// {
// 	if (!ft_strcmp("--all", av))
// 		return (1);
// 	if (!ft_strcmp("--reverse", av))
// 		return (1);
// 	if (!ft_strcmp("--recursive", av))
// 		return (1);
// 	if (!ft_strcmp("--directory", av))
// 		return (1);
// 	if (!ft_strcmp("--color", av))
// 		return (1);
// 	if (!ft_strcmp("--help", av))
// 		return (1);
// 	return (0);
// }

/*	1 true, 0 false
**	Данная функция отвечает за "подгонку" к оригинальной
**	функции - отвечает на вопрос, нужно ли парсить данный
**	аргумент пришедший к нам из CLI. Включает 2 частных
**	случая, когда решение о парсинге аргумента не очевидно  */

int	isFlag(char const *av)
{
	size_t	len;

	len = ft_strlen(av);
	if (len < 1)
		return (0);
	if (len == 2 && av[0] == '-' && av[1] == '-')
		return (1);
	if (av[0] == '-')
		return (1);
	return (0);
}

/*	Частный случай. Оригинальная функция игнорирует этот аргумент
**	Короче это костыль  */

int isNeedToSkipThisFlag(char const *av)
{
	size_t	len;

	len = ft_strlen(av);
	if (len == 2 && av[0] == '-' && av[1] == '-')
		return (1);
	return (0);
}