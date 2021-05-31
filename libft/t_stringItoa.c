#include "libft.h"

static void	itoaToBuf(char *dst, int n)
{
	int				i;
	int				buf;
	unsigned int	temp;

	buf = n;
	i = 1;
	while ((buf = buf / 10))
		i++;
	buf = 0;
	if (n < 0 && (buf = 1))
		temp = (unsigned int)(-n);
	else
		temp = (unsigned int)n;
	dst[i + buf] = '\0';
	while (--i > -1)
	{
		dst[i + buf] = (char)(temp % 10 + '0');
		temp = temp / 10;
	}
	if (buf)
		dst[0] = '-';
}

/*
**	Функция не чистит исходную string структуру в случае ошибки
**	поэтому возвращаемое значение только для признака ошибки
*/

t_string	*stringItoa(t_string *dst, int nbr)
{
	size_t	addLength;
	int 	cpy;

	addLength = 1;
	cpy = nbr;
	while ((cpy = cpy / 10))
		addLength++;
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
	int 	cpy;

	nbrLength = 1;
	cpy = nbr;
	while ((cpy = cpy / 10))
		nbrLength++;
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
	while(addLength > nbrLength)
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
	int 	cpy;

	nbrLength = 1;
	cpy = nbr;
	while ((cpy = cpy / 10))
		nbrLength++;
	if (nbr < 0)
		nbrLength++;
	if (addLength < nbrLength)
		addLength = nbrLength;
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	while(addLength > nbrLength)
	{
		dst->str[dst->length] = c;
		dst->length++;
		addLength--;
	}
	itoaToBuf(&(dst->str[dst->length]), nbr);
	dst->length += nbrLength;
	return (dst);
}