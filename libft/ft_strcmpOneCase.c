#include "libft.h"

// Порядок обработки в функции
// а б в г д е ж з и й к л м н о п
// ё
// р с т у ф х ц ч ш щ ъ ы ь э ю я
// Весь русский алфавит в верхнем регистре кроме Ё
// Ё

static int	isUtf8LocaleRu(char c1, char c2)
{
	if (c1 == -48 && c2 >= -80 && c2 <= -65)
		return (1);
	if (c1 == -47 && c2 == -111)
		return (1);
	if (c1 == -47 && c2 <= -113)
		return (1);
	if (c1 == -48 && c2 >= -112 && c2 <= -81)
		return (1);
	if (c1 == -48 && c2 == -127)
		return (1);
	return (0);
}

// if (c1 < 127 && c2 < 127)
// if (c1 >= 'A' && c1 <= 'Z' && c2 >= 'A' && c2 <= 'Z')
// return ((int)c1 - (int)c2);

static int	ft_strcmpOneCase_handler(unsigned char char1, unsigned char char2)
{
	unsigned char	c1;
	unsigned char	c2;

	c1 = char1;
	c2 = char2;
	if (c1 >= 'a' && c1 <= 'z')
		c1 = c1 - 'a' + 'A';
	if (c2 >= 'a' && c2 <= 'z')
		c2 = c2 - 'a' + 'A';
	if (c1 == c2)
		return ((int)(char2) - (int)(char1));
	return ((int)c1 - (int)c2);
}

int	ft_strcmpOneCase(char const *s1, char const *s2)
{
	int				i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((s1[i] != s2[i] || s1[i + 1] != s2[i + 1]) && \
			isUtf8LocaleRu(s1[i], s1[i + 1]) && \
			isUtf8LocaleRu(s2[i], s2[i + 1]))
			return (cmpUtf8(s1[i], s1[i + 1], s2[i], s2[i + 1]));
		if (s1[i] != s2[i])
		{
			return (ft_strcmpOneCase_handler(s1[i], s2[i]));
		}
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
