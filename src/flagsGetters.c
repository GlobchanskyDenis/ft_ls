#include "ft_ls.h"

int	isSortingDisabled(int flags)
{
	if (!(flags & (1 << SORT_BY_ACCESS)) &&
		!(flags & (1 << SORT_BY_MODIF)) &&
		!(flags & (1 << SORT_BY_NAME)))
		return (1);
	return (0);
}
