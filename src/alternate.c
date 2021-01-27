#include "ft_ls.h"

static char	utf8LocaleRuToAlternateFirst(char c1, char c2)
{
	// а б в г д е ж з и й к л м н о п
	if (c1 == -48 && c2 >= -80 && c2 <= -65)
		return (-48);
	// ё
	if (c1 == -47 && c2 == -111)
		return (-48);
	// р с т у ф х ц ч ш щ ъ ы ь э ю я
	if (c1 == -47 && c2 <= -113) // && c2 >= -128
		return (-48);
	// Весь русский алфавит в верхнем регистре кроме Ё
	if (c1 == -48 && c2 >= -112 && c2 <= -81)
		return (-48);
	// Ё
	if (c1 == -48 && c2 == -127)
		return (-48);
	return (c1);
}

static char	utf8LocaleRuToAlternateSecond(char c1, char c2)
{
	// А Б В Г Д Е
	if (c1 == -48 && c2 >= -112 && c2 <= -107)
		return (c2 - 1);
	// Ё
	if (c1 == -48 && c2 == -127)
		return (-107);
	// ё
	if (c1 == -47 && c2 == -111)
		return (-74);
	// ж з и й к л м н о п
	if (c1 == -48 && c2 >= -74 && c2 <= -65)
		return (c2 + 1);
	// р с т у ф х ц ч ш щ ъ ы ь э ю я (16 букв)
	if (c1 == -47 && c2 <= -113)
		return (c2 + 65);
	// not russian locale or Ж З .. Э Ю Я
	return (c2);
}

static int  shouldPrintNameWithQuotes(char c)
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

int			initAlternateString(char *dst, char *src)
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
			dst[i] = src[i];
			if (shouldPrintNameWithQuotes(dst[i]))
				isNeedQuotes = 1;
		}
		i++;
	}
	dst[i] = '\0';
	return (isNeedQuotes);
}

