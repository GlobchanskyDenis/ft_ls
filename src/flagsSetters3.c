#include "ft_ls.h"

int	setFlagSortByModificationTime(int flags)
{
	flags |= (1 << FLAG_T);
	flags = setSortByModification(flags);
	flags |= (1 << SHOW_MODIF_TIME);
	// if (flags & (1 << FLAG_F))
	// {
	// 	flags = setSortByAccess(flags);
	// }
	if (flags & (1 << FLAG_U))
	{
		flags = setSortByAccess(flags);
		flags |= (1 << SHOW_ACCESS_TIME);
		flags &= ~(1 << SHOW_MODIF_TIME);
	}
	return (flags);
}

int	setFlagSortByAccessTime(int flags)
{
	flags |= (1 << FLAG_U);
	if (flags & (1 << FLAG_T))
	{
		flags = setSortByAccess(flags);
		flags |= (1 << SHOW_ACCESS_TIME);
		flags &= ~(1 << SHOW_MODIF_TIME);
	}
	else if (flags & (1 << FLAG_L))
	{
		flags = setSortByName(flags);
		flags |= (1 << SHOW_ACCESS_TIME);
		flags &= ~(1 << SHOW_MODIF_TIME);
	}
	else
	{
		flags = setSortByAccess(flags);
		flags |= (1 << SHOW_ACCESS_TIME);
		flags &= ~(1 << SHOW_MODIF_TIME);
	}
	return (flags);
}

int	setFlagDisableSort(int flags)
{
	flags |= (1 << FLAG_F);
	flags |= (1 << SEPARATOR_EOL);
	flags |= (1 << SHOW_HIDDEN);
	if (flags & (1 << FLAG_L) || flags & (1 << FLAG_G))
	{
		flags &= ~(1 << SHOW_RIGHTS_GROUP_WEIGHT);
		flags &= ~(1 << SHOW_AUTHOR);
	}
	// if (flags & (1 << FLAG_T))
	// {
	// 	flags |= (1 << SHOW_HIDDEN);
	// }
	flags = setSortDisable(flags);
	return (flags);
}
