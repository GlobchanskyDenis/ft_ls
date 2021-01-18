#include "ft_ls.h"

int		isFileExist(char const *filename)
{
	t_stat		stat;

	if (lstat(filename, &stat) != 0)
		return (0);
	return (1);
}

t_error	*readFileLstat(t_file *file)
{
	t_stat		stat;

	if (lstat(file->name, &stat) != 0)
		return (permissionError(file->name));
	fprint("file %s mode %d ", file->name, stat.st_mode);
	DumpBits(stat.st_mode);
	fprint("\n");
	return (NULL);
}