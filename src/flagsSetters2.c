#include "ft_ls.h"

int	setFlagHiddenA(int flags)
{
	flags |= (1 << FLAG_A);
	flags |= (1 << SHOW_HIDDEN);
	return (flags);
}

int	setFlagOnlyDirectories(int flags)
{
	flags |= (1 << FLAG_D);
	return (flags);
}

int	setFlagReverse(int flags)
{
	flags |= (1 << FLAG_R);
	return (flags);
}

int	setFlagRecursion(int flags)
{
	flags |= (1 << FLAG_RR);
	return (flags);
}
