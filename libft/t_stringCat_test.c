#include "libft.h"

static int	handleStringCatOutput(t_string *string, char *str)
{
	if (string == NULL)
	{
		fprint_fd(2, "String is null\n");
		return (-1);
	}
	if (!(stringCat(string, str)))
	{
		fprint_fd(2, "NULL returned!\n");
		return (0);
	}
	fprint("%s length=%d maxLen=%d\n", string->str, (int)(string->length), \
		(int)(string->maxLen));
	return (0);
}

int	main(void)
{
	t_string	*string;

	string = stringNew(2);
	if (handleStringCatOutput(string, "a") < 0)
		return (-1);
	if (handleStringCatOutput(string, "bcdefghijklmnopqrstuvwxyz") < 0)
		return (-1);
	if (handleStringCatOutput(string, "abcdefg") < 0)
		return (-1);
	if (handleStringCatOutput(string, "hijklmnopqrstuvwxyz") < 0)
		return (-1);
	stringDel(&string);
	return (0);
}
