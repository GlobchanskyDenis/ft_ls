#include "ft_ls.h"

int		isFileExist(char const *filename)
{
	t_stat		stat;

	if (lstat(filename, &stat) != 0)
		return (0);
	return (1);
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
	// fprint("sym link = '%s'\n", file->symlink);
	return (noErrors());
}

static t_error	readAuthorGroupNames(t_file *file)
{
	t_passwd	*pass;
	t_group		*grp;

	if (!(pass = getpwuid(file->stat.st_uid)))
		return (newError(file->name, strerror(errno)));
	// fprint("user name %s passwd %s\n", pass->pw_name, pass->pw_passwd);
	file->author = pass->pw_name;
	if (!(grp = getgrgid(file->stat.st_gid)))
		return (newError(file->name, strerror(errno)));
	// fprint("group name %s passwd %s\n\n", grp->gr_name, grp->gr_passwd);
	file->group = grp->gr_name;
	return (noErrors());
}

t_error			readFileLstat(t_file *file)
{
	t_error	error;

	if (file->name == NULL)
	{
		if (lstat(".", &(file->stat)) != 0)
			return (newError(".", strerror(errno)));
	}
	else
	{
		if (lstat(file->name, &(file->stat)) != 0)
			return (newError(file->name, strerror(errno)));
	}
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

