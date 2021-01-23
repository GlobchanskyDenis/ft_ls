#include "libft.h"

static int		isUtf8LocaleRu(char c1, char c2)
{
	// а б в г д е ж з и й к л м н о п
	if (c1 == -48 && c2 >= -80 && c2 <= -65)
		return (1);
	// ё
	if (c1 == -47 && c2 == -111)
		return (1);
	// р с т у ф х ц ч ш щ ъ ы ь э ю я
	if (c1 == -47 && c2 <= -113) // && c2 >= -128
		return (1);
	// Весь русский алфавит в верхнем регистре кроме Ё
	if (c1 == -48 && c2 >= -112 && c2 <= -81)
		return (1);
	// Ё
	if (c1 == -48 && c2 == -127)
		return (1);
	return (0);
}

static int		isUpperCase(char c1, char c2)
{
	// Весь русский алфавит в верхнем регистре кроме Ё
	if (c1 == -48 && c2 >= -112 && c2 <= -81)
		return (1);
	// Ё
	if (c1 == -48 && c2 == -127)
		return (1);
	return (0);
}

/*
**	In upper case bit 1 always equal char = -48 unsigned char = 208
*/
static char	utf8LocaleRuToUpperBit2(char c1, char c2)
{
	// а б в г д е
	if (c1 == -48 && c2 >= -80 && c2 <= -75)
		return (c2 + 80 - 112);
	// ё
	if (c1 == -47 && c2 == -111)
		return (-127);
	// ж з и й к л м н о п
	if (c1 == -48 && c2 >= -74 && c2 <= -65)
		return (c2 + 74 - 106);
	// р с т у ф х ц ч ш щ ъ ы ь э ю я
	if (c1 == -47 && c2 <= -113) // && c2 >= -128
		return (c2 + 128 - 96);
	// not in locale ru lower case
	return (c2);
}

/*
**	Возвращаю результат сравнения двух букв в utf8
**	в русской локали (оба регистра)
**	Не обработан случай с буквами Ё ё -
**	они могут неправильно сортироваться
*/
int		cmpUtf8(char c11, char c12, char c21, char c22)
{
	char	upCaseC1;
	char	upCaseC2;

	// Если они оба в русской локали и в одном регистре ...
	if (c11 == c21 && isUpperCase(c11, c12) == isUpperCase(c21, c22))
		return ((int)(c12 - c22));
	upCaseC1 = utf8LocaleRuToUpperBit2(c11, c12);
	upCaseC2 = utf8LocaleRuToUpperBit2(c21, c22);
	if (upCaseC1 == upCaseC2)
		return ((int)(c22 - c12));
	return ((int)(upCaseC1 - upCaseC2));
}

int		ft_strcmpOneCase(char const *s1, char const *s2)
{
	int				i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((s1[i] != s2[i] || s1[i + 1] != s2[i + 1]) &&
			isUtf8LocaleRu(s1[i], s1[i + 1]) &&
			isUtf8LocaleRu(s2[i], s2[i + 1]))
			return cmpUtf8(s1[i], s1[i + 1], s2[i], s2[i + 1]);
		if (s1[i] != s2[i])
		{
			c1 = s1[i];
			c2 = s2[i];
			if (c1 >= 'a' && c1 <= 'z')
				c1 = c1 - 'a' + 'A';
			if (c2 >= 'a' && c2 <= 'z')
				c2 = c2 - 'a' + 'A';
			if (c1 == c2)
				return ((int)(s2[i]) - (int)(s1[i]));
			// if (c1 < 127 && c2 < 127)// if (c1 >= 'A' && c1 <= 'Z' && c2 >= 'A' && c2 <= 'Z')
				// return ((int)c1 - (int)c2);
			// fprint("%s %c %d  --- %s %c %d\n", &(((char *)s1)[i]), c1, c1, &(((char *)s2)[i]), c2, c2);
			// if (c1 )
			return ((int)c1 - (int)c2);
			// return ft_cmpUtf8(&((char *)s1[i]), &((char *)s2[i]));
		}
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}