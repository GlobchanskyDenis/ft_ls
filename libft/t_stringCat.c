#include "libft.h"

/*
**	Функция не чистит исходную string структуру в случае ошибки
**	поэтому возвращаемое значение только для признака ошибки
*/

t_string	*stringCat(t_string *dst, char *src)
{
	size_t	addLength;

	addLength = ft_strlen(src);
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	ft_strcpy(&(dst->str[dst->length]), src);
	dst->length += addLength;
	return (dst);
}

/*
**	Функция не чистит исходную string структуру в случае ошибки
**	поэтому возвращаемое значение только для признака ошибки
*/

t_string	*stringCat2(t_string *dst, char *src1, char *src2)
{
	size_t	srcLen1;
	size_t	srcLen2;

	srcLen1 = ft_strlen(src1);
	srcLen2 = ft_strlen(src2);
	if (!stringCheckOverflow(dst->maxLen, srcLen1, srcLen2, 0))
		return (NULL);
	if (!stringGrantSize(dst, srcLen1 + srcLen2))
		return (NULL);
	ft_strcpy(&(dst->str[dst->length]), src1);
	dst->length += srcLen1;
	ft_strcpy(&(dst->str[dst->length]), src2);
	dst->length += srcLen2;
	return (dst);
}

/*
**	Функция не чистит исходную string структуру в случае ошибки
**	поэтому возвращаемое значение только для признака ошибки
*/

t_string	*stringCat3(t_string *dst, char *src1, char *src2, char *src3)
{
	size_t	srcLen1;
	size_t	srcLen2;
	size_t	srcLen3;

	srcLen1 = ft_strlen(src1);
	srcLen2 = ft_strlen(src2);
	srcLen3 = ft_strlen(src3);
	if (!stringCheckOverflow(dst->maxLen, srcLen1, srcLen2, srcLen3))
		return (NULL);
	if (!stringGrantSize(dst, srcLen1 + srcLen2 + srcLen3))
		return (NULL);
	ft_strcpy(&(dst->str[dst->length]), src1);
	dst->length += srcLen1;
	ft_strcpy(&(dst->str[dst->length]), src2);
	dst->length += srcLen2;
	ft_strcpy(&(dst->str[dst->length]), src3);
	dst->length += srcLen3;
	return (dst);
}

/*
**	Функция не чистит исходную string структуру в случае ошибки
**	поэтому возвращаемое значение только для признака ошибки
*/

t_string	*stringCatN(t_string *dst, char *src, size_t n)
{
	size_t	addLength;

	addLength = ft_strlen(src);
	if (n < addLength)
		addLength = n;
	if (dst->maxLen + addLength < dst->maxLen)
		return (NULL);
	if (!stringGrantSize(dst, addLength))
		return (NULL);
	ft_strncpy(&(dst->str[dst->length]), src, n);
	dst->length += addLength;
	return (dst);
}
