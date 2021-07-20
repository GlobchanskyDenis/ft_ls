#include "ft_ls.h"

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

int	isNeedToSkipThisFlag(char const *av)
{
	size_t	len;

	len = ft_strlen(av);
	if (len == 2 && av[0] == '-' && av[1] == '-')
		return (1);
	return (0);
}
