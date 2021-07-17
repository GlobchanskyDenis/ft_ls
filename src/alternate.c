#include "ft_ls.h"

/*
**	а б в г д е ж з и й к л м н о п
**	ё
**	р с т у ф х ц ч ш щ ъ ы ь э ю я
**	Whole russian alphabet in upper case except Ё
**	Ё
*/

static char	utf8LocaleRuToAlternateFirst(char c1, char c2)
{
	if (c1 == -48 && c2 >= -80 && c2 <= -65)
		return (-48);
	if (c1 == -47 && c2 == -111)
		return (-48);
	if (c1 == -47 && c2 <= -113)
		return (-48);
	if (c1 == -48 && c2 >= -112 && c2 <= -81)
		return (-48);
	if (c1 == -48 && c2 == -127)
		return (-48);
	return (c1);
}

/*
**	А Б В Г Д Е
**	Ё
**	ё
**	ж з и й к л м н о п
**	р с т у ф х ц ч ш щ ъ ы ь э ю я
**	not russian locale or Ж З .. Э Ю Я
*/

static char	utf8LocaleRuToAlternateSecond(char c1, char c2)
{
	if (c1 == -48 && c2 >= -112 && c2 <= -107)
		return (c2 - 1);
	if (c1 == -48 && c2 == -127)
		return (-107);
	if (c1 == -47 && c2 == -111)
		return (-74);
	if (c1 == -48 && c2 >= -74 && c2 <= -65)
		return (c2 + 1);
	if (c1 == -47 && c2 <= -113)
		return (c2 + 65);
	return (c2);
}

/*
**	If some characters are contained in the name - the entire
**	name must be displayed in apostrophes. This function returns
**	an indication of the presence of such a symbol.
*/

static int	shouldPrintNameWithQuotes(char c)
{
	if (c > 31 && c < 37)
		return (1);
	if (c > 37 && c < 43)
		return (1);
	if (c > 58 && c < 64)
		return (1);
	if (c > 122 && c < 127)
		return (1);
	if (c == 91 || c == 92 || c == 94 || c == 96)
		return (1);
	return (0);
}

/*	Костыль для последующей сортировки. Отправляет LowCase в UpCase
**	и наоборот в зависимости от того, какой флаг был включен */

static char	changeTextCases(char c, int flags)
{
	if (flags & (1 << FLAG_T))
	{
		// if (c >= 'a' && c <= 'z')
		// 	return (c - 'a' + 'A');
		// if (c >= 'A' && c <= 'Z')
		// 	return (c - 'A' + 'a');
		
		// if (c == '.')
		// 	return (126);
	}
	return (c);
}

/*	Альтернативное имя используется для корректной сортировки русского
**	алфавита а также в качестве костыля (на моей Ubuntu даже при
**	включенной локали я получаю некорректную сортировку по имени в случаях
**	когда первичная сортировка идет по времени (модификации / доступа).
**	Сортировка отличается при флагах -u -t).
**	Поэтому я передаю аргументом в эту функцию флаги, хотя в такой
**	низкоуровневой функции это выглядит странно  */

int	initAlternateString(char *dst, char *src, int flags)
{
	size_t	i;
	size_t	len;
	int		isNeedQuotes;

	len = ft_strlen(src);
	isNeedQuotes = 0;
	i = 0;
	while (i < len && src[i])
	{
		if (src[i] < 0)
		{
			dst[i] = utf8LocaleRuToAlternateFirst(src[i], src[i + 1]);
			dst[i + 1] = utf8LocaleRuToAlternateSecond(src[i], src[i + 1]);
			i++;
		}
		else
		{
			dst[i] = changeTextCases(src[i], flags);
			if (shouldPrintNameWithQuotes(src[i]))
				isNeedQuotes = 1;
		}
		i++;
	}
	dst[i] = '\0';
	return (isNeedQuotes);
}
