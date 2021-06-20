#include "libft.h"

int	stringCheckOverflow(size_t len1, size_t len2,
	size_t len3, size_t len4)
{
	if (len1 + len2 < len1 || len1 + len2 + len3 < len1 + len2 || \
		len1 + len2 + len3 + len4 < len1 + len2 + len3)
		return (0);
	return (1);
}

t_string	*increaseStringLength(t_string *dst, size_t addLength)
{
	char	*newStringBuffer;
	size_t	newMaxLen;

	newMaxLen = dst->maxLen;
	while (newMaxLen < dst->length + addLength)
		newMaxLen *= 5;
	newStringBuffer = (char *)malloc(newMaxLen + 1);
	if (!newStringBuffer)
		return (NULL);
	ft_strcpy(newStringBuffer, dst->str);
	free(dst->str);
	dst->str = newStringBuffer;
	dst->maxLen = newMaxLen;
	return (dst);
}

t_string	*stringGrantSize(t_string *dst, size_t size)
{
	if (dst->maxLen - dst->length >= size)
		return (dst);
	if (!increaseStringLength(dst, size))
		return (NULL);
	return (dst);
}
