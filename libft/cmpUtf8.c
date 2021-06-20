#include "libft.h"

// Порядок обработки в функции
// Весь русский алфавит в верхнем регистре кроме Ё
// Ё

static int	isUpperCase(char c1, char c2)
{
	if (c1 == -48 && c2 >= -112 && c2 <= -81)
		return (1);
	if (c1 == -48 && c2 == -127)
		return (1);
	return (0);
}

/*
**	In upper case bit 1 always equal char = -48 unsigned char = 208
*/

// Порядок обработки в функции
// а б в г д е
// ё
// ж з и й к л м н о п
// р с т у ф х ц ч ш щ ъ ы ь э ю я
// return means not in locale ru lower case

static char	utf8LocaleRuToUpperBit2(char c1, char c2)
{
	if (c1 == -48 && c2 >= -80 && c2 <= -75)
		return (c2 + 80 - 112);
	if (c1 == -47 && c2 == -111)
		return (-127);
	if (c1 == -48 && c2 >= -74 && c2 <= -65)
		return (c2 + 74 - 106);
	if (c1 == -47 && c2 <= -113)
		return (c2 + 128 - 96);
	return (c2);
}

/*
**	Возвращаю результат сравнения двух букв в utf8
**	в русской локали (оба регистра)
**	Не обработан случай с буквами Ё ё -
**	они могут неправильно сортироваться
*/

// Первое возвращение - Если они оба в русской локали и в одном регистре ...

int	cmpUtf8(char c11, char c12, char c21, char c22)
{
	char	upCaseC1;
	char	upCaseC2;

	if (c11 == c21 && isUpperCase(c11, c12) == isUpperCase(c21, c22))
		return ((int)(c12 - c22));
	upCaseC1 = utf8LocaleRuToUpperBit2(c11, c12);
	upCaseC2 = utf8LocaleRuToUpperBit2(c21, c22);
	if (upCaseC1 == upCaseC2)
		return ((int)(c22 - c12));
	return ((int)(upCaseC1 - upCaseC2));
}
