#include "libft.h"

char	*ft_bufconcat2(char *dst, char *src1, char *src2)
{
	size_t	length1;
	size_t	length2;

	length1 = ft_strlen(src1);
	length2 = ft_strlen(src2);
	if ((length1 > length1 + length2) || (length1 + length2 > \
		length1 + length2 + 1))
		return (NULL);
	ft_strcpy(dst, src1);
	ft_strcpy(&(dst[length1]), src2);
	dst[length1 + length2] = '\0';
	return (dst);
}

char	*ft_bufconcat3(char *dst, char *src1, char *src2, char *src3)
{
	size_t	length1;
	size_t	length2;
	size_t	length3;

	length1 = ft_strlen(src1);
	length2 = ft_strlen(src2);
	length3 = ft_strlen(src3);
	if ((length1 > length1 + length2) || (length1 + length2 > \
		length1 + length2 + length3) || (length1 + length2 + length3 > \
		length1 + length2 + length3 + 1))
		return (NULL);
	ft_strcpy(dst, src1);
	ft_strcpy(&(dst[length1]), src2);
	ft_strcpy(&(dst[length1 + length2]), src3);
	dst[length1 + length2 + length3] = '\0';
	return (dst);
}
