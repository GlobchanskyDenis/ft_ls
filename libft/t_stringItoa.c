#include "libft.h"

static size_t	itoa_countRanks(int n)
{
	size_t	ranks;

	ranks = 1;
	n = n / 10;
	while (n)
	{
		ranks++;
		n = n / 10;
	}
	return (ranks);
}

void	itoaToBuf(char *dst, int n)
{
	int				ranks;
	int				sign;
	unsigned int	temp;

	ranks = itoa_countRanks(n);
	sign = 0;
	if (n < 0)
	{
		temp = (unsigned int)(-n);
		sign = 1;
	}
	else
		temp = (unsigned int)n;
	dst[ranks + sign] = '\0';
	while (--ranks > -1)
	{
		dst[ranks + sign] = (char)(temp % 10 + '0');
		temp = temp / 10;
	}
	if (sign)
		dst[0] = '-';
}

/*
**	Функция не чистит исходную string структуру в случае ошибки
**	поэтому возвращаемое значение только для признака ошибки
*/

t_string	*stringItoa(t_string *dst, int nbr)
{
	size_t	addLength;

	addLength = itoa_countRanks(nbr);
	if (nbr < 0)
		addLength++;
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	itoaToBuf(&(dst->str[dst->length]), nbr);
	dst->length += addLength;
	return (dst);
}

t_string	*stringItoaAlignL(t_string *dst, int nbr, size_t addLength, char c)
{
	size_t	nbrLength;

	nbrLength = itoa_countRanks(nbr);
	if (nbr < 0)
		nbrLength++;
	if (addLength < nbrLength)
		addLength = nbrLength;
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	itoaToBuf(&(dst->str[dst->length]), nbr);
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

t_string	*stringItoaAlignR(t_string *dst, int nbr, size_t addLength, char c)
{
	size_t	nbrLength;

	nbrLength = itoa_countRanks(nbr);
	if (nbr < 0)
		nbrLength++;
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
	itoaToBuf(&(dst->str[dst->length]), nbr);
	dst->length += nbrLength;
	return (dst);
}
