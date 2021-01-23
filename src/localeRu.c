#include "ft_ls.h"

int		isUtf8LocaleRu(char c1, char c2)
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

int		isUpperCase(char c1, char c2)
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
char	utf8LocaleRuToUpperBit2(char c1, char c2)
{
	// а б в г д е
	if (c1 == -48 && c2 >= -80 && c2 <= -75)
		return (c2 + 80 - 112);
	// ё
	if (c1 == -47 && c2 == -111)
		return (-107);//(-127); // возвращаю букву Е
	// Ё
	if (c1 == -48 && c2 == -127)
		return (-107);// возвращаю букву Е
	// ж з и й к л м н о п
	if (c1 == -48 && c2 >= -74 && c2 <= -65)
		return (c2 + 74 - 106);
	// р с т у ф х ц ч ш щ ъ ы ь э ю я
	if (c1 == -47 && c2 <= -113) // && c2 >= -128
		return (c2 + 128 - 96);
	// not in locale ru lower case
	return (c2);
}

int		stringToUpCase(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0 && isUtf8LocaleRu(str[i], str[i + 1]))
		{
			str[i + 1] = utf8LocaleRuToUpperBit2(str[i], str[i + 1]);
			str[i] = -48;
			i++;
		}
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 'a' + 'A';
		i++;
	}
	return (0);
}