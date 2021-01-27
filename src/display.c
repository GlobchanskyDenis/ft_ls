#include "ft_ls.h"

t_error	displayShortDirectory(t_string *buf, t_file *head, int *wasPrintedFirstFile)
{
	t_file		*file;

	file = head;
	while (file)
	{
		if (file->child != NULL && (file = file->next))
			continue ;
		if (*wasPrintedFirstFile)
		{
			if (!stringCat(buf, "  ") && stringDel(&buf))
				return (allocateFailed());
		}
		else
			*wasPrintedFirstFile = 1;
		if (!stringCat(buf, file->name) && stringDel(&buf))
				return (allocateFailed());
		file = file->next;
	}
	if (!stringCat(buf, "\n"))
		return (allocateFailed());
	return (noErrors());
}

t_error	displayShortFiles(t_string *buf, t_file *head)
{
	t_file	*file;
	t_error	error;
	int		wasPrintedFirstFile;

	wasPrintedFirstFile = 0;
	file = head;
	while (file)
	{
		if (file->child != NULL)
		{
			file = file->next;
			continue ;
		}
		if (wasPrintedFirstFile)
		{
			if (!stringCat(buf, "  "))
				return (allocateFailed());
		}
		else
			wasPrintedFirstFile = 1;
		if (file->isNeedQuotes)
		{
			if (!stringCat(buf, "'"))
				return (allocateFailed());
		}
		if (!stringCat(buf, file->name))
			return (allocateFailed());
		if (file->isNeedQuotes)
		{
			if (!stringCat(buf, "'"))
				return (allocateFailed());
		}
		file = file->next;
	}

	file = head;
	while (file)
	{
		if (file->child == NULL)
		{
			file = file->next;
			continue ;
		}
		if (wasPrintedFirstFile)
		{
			if (!stringCat(buf, "\n\n"))
				return (allocateFailed());
		} else
			wasPrintedFirstFile = 1;
		if (file->isNeedQuotes)
		{
			if (!stringCat(buf, "'"))
				return (allocateFailed());
		}
		if (file->path != NULL)
		{
			if (!stringCat(buf, file->path))
				return (allocateFailed());
			if (!stringCat(buf, "/"))
				return (allocateFailed());
		}
		if (!stringCat(buf, file->name))
			return (allocateFailed());
		if (file->isNeedQuotes)
		{
			if (!stringCat(buf, "'"))
				return (allocateFailed());
		}
		if (!stringCat(buf, ":\n"))
			return (allocateFailed());
		error = displayShortFiles(buf, file->child);
		if (error.wasSet)
			return (error);
		file = file->next;
	}
	return (noErrors());
}

t_error displayLongFileTree(int flags, t_file *head)
{
	if (flags && !flags)
		head->name = NULL;
	return (noErrors());
}

t_error	displayFileTree(int flags, t_file *head)
{
	t_string	*buf;
	t_error		error;

	if (!(buf = stringNew(10000)))
		return (allocateFailed());
	if (flags & FLAG_L)
	{
		error = displayLongFileTree(flags, head);
		if (error.wasSet && stringDel(&buf))
			return (error);
	}
	else
	{
		error = displayShortFiles(buf, head);
		if (error.wasSet && stringDel(&buf))
			return (error);
	}
	fprint("%s\n", buf->str);
	stringDel(&buf);
	return (noErrors());
}