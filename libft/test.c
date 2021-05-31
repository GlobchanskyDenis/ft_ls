#include "libft.h"

int		main(void)
{
	t_string	*string;

	if (!(string = stringNew(2)))
	{
		fprint("NULL returned!\n");
		return (0);
	}
	fprint("%s length=%d maxLen=%d\n", string->str, (int)(string->length), (int)(string->maxLen));
	if (!(stringCat(string, "a")))
	{
		fprint("NULL returned!\n");
		return (0);
	}
	fprint("%s length=%d maxLen=%d\n", string->str, (int)(string->length), (int)(string->maxLen));
	if (!(stringCat(string, "bcdefghijklmnopqrstuvwxyz")))
	{
		fprint("NULL returned!\n");
		return (0);
	}
	fprint("%s length=%d maxLen=%d\n", string->str, (int)(string->length), (int)(string->maxLen));
	if (!(stringCat(string, "abcdefg")))
	{
		fprint("NULL returned!\n");
		return (0);
	}
	fprint("%s length=%d maxLen=%d\n", string->str, (int)(string->length), (int)(string->maxLen));
	if (!(stringCat(string, "hijklmnopqrstuvwxyz")))
	{
		fprint("NULL returned!\n");
		return (0);
	}
	fprint("%s length=%d maxLen=%d\n", string->str, (int)(string->length), (int)(string->maxLen));
	stringDel(&string);
	return (0);
}