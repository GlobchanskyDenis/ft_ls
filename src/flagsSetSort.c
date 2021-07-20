#include "ft_ls.h"

int	setSortByName(int flags)
{
	flags |= (1 << SORT_BY_NAME);
	flags &= ~(1 << SORT_BY_MODIF);
	flags &= ~(1 << SORT_BY_ACCESS);
	return (flags);
}

int	setSortByModification(int flags)
{
	flags |= (1 << SORT_BY_MODIF);
	flags &= ~(1 << SORT_BY_NAME);
	flags &= ~(1 << SORT_BY_ACCESS);
	return (flags);
}

int	setSortByAccess(int flags)
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
