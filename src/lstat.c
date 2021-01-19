#include "ft_ls.h"

int		isFileExist(char const *filename)
{
	t_stat		stat;

	if (lstat(filename, &stat) != 0)
		return (0);
	return (1);
}

t_error	readFileLstat(t_file *file)
{
	if (file->name == NULL)
	{
		if (lstat(".", &(file->stat)) != 0)
			return (permissionError("."));
	}
	else
	{
		if (lstat(file->name, &(file->stat)) != 0)
			return (permissionError(file->name));
	}
	// fprint("file %s количество жестких ссылок %d, байт %d время %s\n",
	// 	file->name, file->stat.st_nlink, file->stat.st_size, ctime(&(file->stat.st_atime)));
	if (file->type == SYMBOLIC)
	{
		char	buf[256];
		int		ret;
		if ((ret = readlink(file->name, buf, 256)) == -1)
			return (newError("Cannot access to readlink of symlink"));
		if (!(file->symlink = ft_strdup(buf)))
			return (allocateFailed());
		// fprint("sym link = '%s'\n", buf);
	}
	
	

	return (noErrors());
}