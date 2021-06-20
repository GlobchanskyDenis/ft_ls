#include "libft.h"

t_string	*stringCatAlignR(t_string *dst, char *src, size_t addLength, char c)
{
	size_t	strLength;

	strLength = ft_strlen(src);
	if (addLength < strLength)
		addLength = strLength;
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	while (addLength > strLength)
	{
		dst->str[dst->length] = c;
		dst->length++;
		addLength--;
	}
	ft_strcpy(&(dst->str[dst->length]), src);
	dst->length += strLength;
	return (dst);
}

t_string	*stringCatAlignL(t_string *dst, char *src, size_t addLength, char c)
{
	size_t	strLength;

	strLength = ft_strlen(src);
	if (addLength < strLength)
		addLength = strLength;
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	ft_strcpy(&(dst->str[dst->length]), src);
	dst->length += strLength;
	while (addLength > strLength)
	{
		dst->str[dst->length] = c;
		dst->length++;
		addLength--;
	}
	dst->str[dst->length] = '\0';
	return (dst);
}
