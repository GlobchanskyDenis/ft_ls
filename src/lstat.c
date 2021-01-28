#include "ft_ls.h"

/*
**	Functions that reads file metadata.
*/

int		isFileNotExist(char const *filename)
{
	t_stat		stat;

	if (lstat(filename, &stat) != 0)
		return (errno);
	return (0);
}

static t_error	readSymLink(t_file *file)
{
	char	buf[256];
	int		ret;

	if ((ret = readlink(file->name, buf, 256)) == -1)
		return (newError(file->name, strerror(errno)));
	if (!(file->symlink = ft_strnew(ret)))
		return (allocateFailed());
	ft_strncpy(file->symlink, buf, ret);
	return (noErrors());
}

static t_error	readAuthorGroupNames(t_file *file)
{
	t_passwd	*pass;
	t_group		*grp;

	if (!(pass = getpwuid(file->stat.st_uid)))
		return (newError(file->name, strerror(errno)));
	file->author = pass->pw_name;
	if (!(grp = getgrgid(file->stat.st_gid)))
		return (newError(file->name, strerror(errno)));
	file->group = grp->gr_name;
	return (noErrors());
}

t_error			readFileLstat(t_file *file)
{
	t_error	error;

	if (lstat(file->name, &(file->stat)) != 0)
		return (newError(file->name, strerror(errno)));
	file->type = file->stat.st_mode >> 12;
	if (file->type == SYMBOLIC)
	{
		error = readSymLink(file);
		if (error.wasSet)
			return (error);
	}
	error = readAuthorGroupNames(file);
	if (error.wasSet)
		return (error);
	return (noErrors());
}

