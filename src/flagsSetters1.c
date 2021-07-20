#include "ft_ls.h"

int	setFlagLong(int flags)
{
	flags |= (1 << FLAG_L);
	flags |= (1 << SEPARATOR_EOL);
	flags |= (1 << SHOW_RIGHTS_GROUP_WEIGHT);
	if (!(flags & (1 << FLAG_G)))
		flags |= (1 << SHOW_AUTHOR);
	if (flags & (1 << FLAG_U))
	{
		flags = setSortByAccess(flags);
	}
	return (flags);
}

int	setFlagInColumn(int flags)
{
	flags |= (1 << FLAG_1);
	flags |= (1 << SEPARATOR_EOL);
	return (flags);
}

int	setFlagLongWithoutAuthor(int flags)
{
	flags |= (1 << FLAG_G);
	flags |= (1 << SEPARATOR_EOL);
	flags |= (1 << SHOW_RIGHTS_GROUP_WEIGHT);
	if (flags & (1 << FLAG_L))
		flags &= ~(1 << SHOW_AUTHOR);
	return (flags);
}
