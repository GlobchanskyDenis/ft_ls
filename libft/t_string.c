#include "libft.h"

t_string	*stringNew(size_t maxLen)
{
	t_string	*newString;

	if (maxLen > maxLen + 1)
		return (NULL);
	if (!(newString = (t_string *)ft_memalloc(sizeof(t_string))))
		return (NULL);
	newString->length = 0;
	newString->maxLen = maxLen;
	if (!(newString->str = (char *)ft_memalloc(maxLen + 1)))
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
	if (!(newString = (t_string *)ft_memalloc(sizeof(t_string))))
		return (NULL);
	if (srcLength > maxLen)
		maxLen = srcLength;
	if (!(newString->str = (char *)ft_memalloc(maxLen + 1)))
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
	if (!(dst = stringDup(src1, maxLen)))
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
	if (!(dst = stringDup(src1, maxLen)))
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

/*
**	Функция не чистит исходную string структуру в случае ошибки
**	поэтому возвращаемое значение только для признака ошибки
*/
t_string	*stringCat(t_string *dst, char *src)
{
	size_t	addLength;
	size_t	newMaxLen;
	char	*newCharStr;

	addLength = ft_strlen(src);
	if (dst->maxLen - dst->length >= addLength)
	{
		ft_strcat(&((dst->str)[dst->length]), src);
		dst->length += addLength;
		return (dst);
	}
	newMaxLen = dst->maxLen;
	while(newMaxLen < dst->length + addLength)
		newMaxLen *= 5;
	if (!(newCharStr = (char *)ft_memalloc(newMaxLen + 1)))
		return (NULL);
	ft_strcat(newCharStr, dst->str);
	ft_strcat(&(newCharStr[dst->length]), src);
	dst->length += addLength;
	dst->maxLen = newMaxLen;
	free(dst->str);
	dst->str = newCharStr;
	return (dst);
}

void	stringDel(t_string **src)
{
	t_string	*toDelete;

	if (src == NULL || *src == NULL)
		return ;
	toDelete = *src;
	if (toDelete->str != NULL)
		free(toDelete->str);
	free(toDelete);
	*src = NULL;
}