#include "ft_ls.h"

int	handleFlags(int flags)
{
	if (flags & (1 << FLAG_U))
	{
		flags |= (1 << SORT_BY_ACCESS);
		flags |= (1 << SHOW_ACCESS_TIME);
	}
	if (flags & (1 << FLAG_T))
	{
		flags |= (1 << SORT_BY_MODIF);
		flags |= (1 << SHOW_MODIF_TIME);
	}
	/*	Костыль - выключаю сортировку по времени доступа - должно
	**	сортироваться по имени, но показывать время доступа  */
	if ((flags & (1 << FLAG_U)) && (flags & (1 << FLAG_L)))
		flags = flags ^ (1 << SORT_BY_ACCESS);
	return (flags);
}