#include "ft_ls.h"

// int	handleFlags(int flags)
// {
// 	if ((flags & (1 << FLAG_U)) && (flags & (1 << FLAG_T)))
// 	{
// 		flags |= (1 << SORT_BY_ACCESS);
// 		flags |= (1 << SHOW_ACCESS_TIME);
// 	}
// 	else if (flags & (1 << FLAG_U))
// 	{
// 		if (!(flags & (1 << FLAG_L)))
// 			flags |= (1 << SORT_BY_ACCESS);
// 		flags |= (1 << SHOW_ACCESS_TIME);
// 	}
// 	else if (flags & (1 << FLAG_T))
// 	{
// 		flags |= (1 << SORT_BY_MODIF);
// 		flags |= (1 << SHOW_MODIF_TIME);
// 	}

// 	if (flags & (1 << FLAG_F))
// 	{
// 		flags |= (1 << FLAG_1);
// 		flags &= ~(1 << FLAG_L);
// 		if (flags & (1 << FLAG_T))
// 			flags |= (1 << SORT_BY_ACCESS);
// 	}
// 	return (flags);
// }
