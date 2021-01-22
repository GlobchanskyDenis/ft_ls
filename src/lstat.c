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
		char	buf[257];
		int		ret;
		if ((ret = readlink(file->name, buf, 256)) == -1)
			return (newError("Cannot access to readlink of symlink"));
		if (!(file->symlink = ft_strnew(ret)))
			return (allocateFailed());
		ft_strncpy(file->symlink, buf, ret);
		fprint("sym link = '%s'\n", file->symlink);
	}
	
	// fprint("--- file %s ---\n", file->name);
	t_passwd *pass;

	if (!(pass = getpwuid(file->stat.st_uid)))
		return (newError("Cannot access to user name and password by its ID"));
	// fprint("user name %s passwd %s\n", pass->pw_name, pass->pw_passwd);
	file->author = pass->pw_name;
	t_group *grp;

	if (!(grp = getgrgid(file->stat.st_gid)))
		return (newError("Cannot access to group name and password by its ID"));
	// fprint("group name %s passwd %s\n\n", grp->gr_name, grp->gr_passwd);
	file->group = grp->gr_name;
	return (noErrors());
}