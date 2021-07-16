#include "ft_ls.h"

int	handleFlags(int flags)
{
	if ((flags & (1 << FLAG_U)) && (flags & (1 << FLAG_T)))
	{
		flags |= (1 << SORT_BY_ACCESS);
		flags |= (1 << SHOW_ACCESS_TIME);
	}
	else if (flags & (1 << FLAG_U))
	{
		if (!(flags & (1 << FLAG_L)))
			flags |= (1 << SORT_BY_ACCESS);
		flags |= (1 << SHOW_ACCESS_TIME);
	}
	else if (flags & (1 << FLAG_T))
	{
		flags |= (1 << SORT_BY_MODIF);
		flags |= (1 << SHOW_MODIF_TIME);
	}

	if (flags & (1 << FLAG_F))
	{
		flags |= (1 << FLAG_1);
		flags &= ~(1 << FLAG_L);
		if (flags & (1 << FLAG_T))
			flags |= (1 << SORT_BY_ACCESS);
	}
	return (flags);
}

//////////////////////////////////////////////

int setSortByName(int flags)
{
	flags |= (1 << SORT_BY_NAME);
	flags &= ~(1 << SORT_BY_MODIF);
	flags &= ~(1 << SORT_BY_ACCESS);
	return (flags);
}

int setSortByModification(int flags)
{
	flags |= (1 << SORT_BY_MODIF);
	flags &= ~(1 << SORT_BY_NAME);
	flags &= ~(1 << SORT_BY_ACCESS);
	return (flags);
}

int setSortByAccess(int flags)
{
	flags |= (1 << SORT_BY_ACCESS);
	flags &= ~(1 << SORT_BY_NAME);
	flags &= ~(1 << SORT_BY_MODIF);
	return (flags);
}

int	setSortDisable(int flags)
{
	flags &= ~(1 << SORT_BY_ACCESS);
	flags &= ~(1 << SORT_BY_NAME);
	flags &= ~(1 << SORT_BY_MODIF);
	return (flags);
}

//////////////////////////////////////////////

int	setFlagF(int flags)
{
	flags |= (1 << FLAG_F);
	flags |= (1 << FLAG_1);
	flags &= ~(1 << FLAG_L);
	flags &= ~(1 << FLAG_G);
	if (flags & (1 << FLAG_T))
	{
		flags |= (1 << FLAG_A);
	}
	return (setSortDisable(flags));
}

int	setFlagT(int flags)
{
	flags |= (1 << FLAG_T);
	flags |= (1 << SORT_BY_MODIF);
	flags |= (1 << SHOW_MODIF_TIME);
	if (flags & (1 << FLAG_F))
	{
		flags = setSortByAccess(flags);
	}
	if (flags & (1 << FLAG_U))
	{
		flags = setSortByAccess(flags);
		flags |= (1 << SHOW_ACCESS_TIME);
		flags &= ~(1 << SHOW_MODIF_TIME);
	}
	return (flags);
}

int	setFlagU(int flags)
{
	flags |= (1 << FLAG_U);
	if (!(flags & (1 << FLAG_L)))
	{
		flags = setSortByAccess(flags);
	}
	flags |= (1 << SHOW_ACCESS_TIME);
	if (flags & (1 << FLAG_T))
	{
		flags = setSortByAccess(flags);
		flags |= (1 << SHOW_ACCESS_TIME);
		flags &= ~(1 << SHOW_MODIF_TIME);
	}
	return (flags);
}

int setFlagL(int flags)
{
	flags |= (1 << FLAG_L);
	if (flags & (1 << FLAG_U))
	{
		flags |= (1 << SORT_BY_ACCESS);
		flags &= ~(1 << SORT_BY_MODIF);
	}
	return (flags);
}
