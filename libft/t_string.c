#include "libft.h"

t_string	*stringNew(size_t maxLen)
{
	t_string	*newString;

	if (maxLen > maxLen + 1)
		return (NULL);
	newString = (t_string *)ft_memalloc(sizeof(t_string));
	if (!newString)
		return (NULL);
	newString->length = 0;
	newString->maxLen = maxLen;
	newString->str = (char *)ft_memalloc(maxLen + 1);
	if (!(newString->str))
	{
		free(newString);
		return (NULL);
	}
	return (newString);
}

t_string	*stringDup(char *srcLine, size_t maxLen)
{
	t_string	*newString;
	size_t		srcLength;

	srcLength = ft_strlen(srcLine);
	if ((maxLen > maxLen + 1) || (srcLength > srcLength + 1))
		return (NULL);
	newString = (t_string *)ft_memalloc(sizeof(t_string));
	if (!newString)
		return (NULL);
	if (srcLength > maxLen)
		maxLen = srcLength;
	newString->str = (char *)ft_memalloc(maxLen + 1);
	if (!(newString->str))
	{
		free(newString);
		return (NULL);
	}
	ft_strcpy(newString->str, srcLine);
	newString->length = srcLength;
	newString->maxLen = maxLen;
	return (newString);
}

t_string	*stringConcat2(char *src1, char *src2, size_t maxLen)
{
	size_t		length1;
	size_t		length2;
	t_string	*dst;

	length1 = ft_strlen(src1);
	length2 = ft_strlen(src2);
	if (length1 + length2 + 1 > maxLen)
		maxLen = length1 + length2 + 1;
	dst = stringDup(src1, maxLen);
	if (!dst)
		return (NULL);
	if (!stringCat(dst, src2))
	{
		stringDel(&dst);
		return (NULL);
	}
	return (dst);
}

t_string	*stringConcat3(char *src1, char *src2, char *src3, size_t maxLen)
{
	size_t		length1;
	size_t		length2;
	size_t		length3;
	t_string	*dst;

	length1 = ft_strlen(src1);
	length2 = ft_strlen(src2);
	length3 = ft_strlen(src3);
	if (length1 + length2 + length3 + 1 > maxLen)
		maxLen = length1 + length2 + length3 + 1;
	dst = stringDup(src1, maxLen);
	if (!dst)
		return (NULL);
	if (!stringCat(dst, src2))
	{
		stringDel(&dst);
		return (NULL);
	}
	if (!stringCat(dst, src3))
	{
		stringDel(&dst);
		return (NULL);
	}
	return (dst);
}

int	stringDel(t_string **src)
{
	t_string	*toDelete;

	if (src == NULL || *src == NULL)
		return (0);
	toDelete = *src;
	if (toDelete->str != NULL)
		free(toDelete->str);
	free(toDelete);
	*src = NULL;
	return (1);
}
