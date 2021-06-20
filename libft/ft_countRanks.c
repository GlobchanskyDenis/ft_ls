#include "libft.h"

size_t	countRanksSizeT(size_t value, int base)
{
	size_t	ranks;

	ranks = 1;
	value = value / base;
	while (value)
	{
		ranks++;
		value = value / base;
	}
	return (ranks);
}

size_t	countRanksLLsigned(long long value, int base)
{
	size_t	ranks;

	ranks = 1;
	if (value < 0)
	{
		ranks++;
		value = -value;
	}
	value = value / base;
	while (value)
	{
		ranks++;
		value = value / base;
	}
	return (ranks);
}
