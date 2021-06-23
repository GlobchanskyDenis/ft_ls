#include "libft.h"

void	sizeTtoBuf(char *dst, size_t n)
{
	size_t			ranks;

	ranks = countRanksSizeT(n, 10);
	dst[ranks] = '\0';
	while (1)
	{
		ranks--;
		dst[ranks] = (char)(n % 10 + '0');
		n = n / 10;
		if (ranks == 0)
			break ;
	}
}

/*
**	Функция не чистит исходную string структуру в случае ошибки
**	поэтому возвращаемое значение только для признака ошибки
*/

t_string	*stringSizeTtoa(t_string *dst, size_t nbr)
{
	size_t	addLength;

	addLength = countRanksSizeT(nbr, 10);
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	sizeTtoBuf(&(dst->str[dst->length]), nbr);
	dst->length += addLength;
	return (dst);
}

t_string	*stringSizeTtoaAlignL(t_string *dst, size_t nbr, size_t addLength, \
	char c)
{
	size_t	nbrLength;

	nbrLength = countRanksSizeT(nbr, 10);
	if (addLength < nbrLength)
		addLength = nbrLength;
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	sizeTtoBuf(&(dst->str[dst->length]), nbr);
	dst->length += nbrLength;
	while (addLength > nbrLength)
	{
		dst->str[dst->length] = c;
		dst->length++;
		addLength--;
	}
	dst->str[dst->length] = '\0';
	return (dst);
}

t_string	*stringSizeTtoaAlignR(t_string *dst, size_t nbr, size_t addLength, \
	char c)
{
	size_t	nbrLength;

	nbrLength = countRanksSizeT(nbr, 10);
	if (addLength < nbrLength)
		addLength = nbrLength;
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	while (addLength > nbrLength)
	{
		dst->str[dst->length] = c;
		dst->length++;
		addLength--;
	}
	sizeTtoBuf(&(dst->str[dst->length]), nbr);
	dst->length += nbrLength;
	return (dst);
}
