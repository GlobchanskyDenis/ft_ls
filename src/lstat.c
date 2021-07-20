#include "ft_ls.h"

/*
**	Functions that reads file metadata.
*/

static t_error	readSymLink(t_file *file)
{
	char	buf[256];
	int		ret;

	ret = readlink(file->fullpath, buf, 256);
	if (ret == -1)
		return (newError(file->fullpath, strerror(errno)));
	file->symlink = ft_strnew(ret);
	if (!(file->symlink))
		return (allocateFailed());
	ft_strncpy(file->symlink, buf, ret);
	return (noErrors());
}

static t_error	readAuthorGroupNames(t_file *file)
{
	struct passwd	*pass;
	struct group	*grp;

	pass = getpwuid(file->stat.st_uid);
	if (!pass)
		return (newError(file->fullpath, strerror(errno)));
	if (ft_strlen(pass->pw_name) > MAX_FILENAME)
		return (newError(file->fullpath, "too long author name"));
	ft_strcpy(file->author, pass->pw_name);
	grp = getgrgid(file->stat.st_gid);
	if (!grp)
		return (newError(file->fullpath, strerror(errno)));
	if (ft_strlen(grp->gr_name) > MAX_FILENAME)
		return (newError(file->fullpath, "too long group name"));
	ft_strcpy(file->group, grp->gr_name);
	return (noErrors());
}

/*
**	Считывает расширенное значение атрибутов (для отображения
**	их присутствия при включенных флагах -la).
*/

static t_error	readFileACL(t_file *file)
{
	ssize_t	result;
	char	list[256];

	result = listxattr(file->fullpath, list, 255);
	if (result < 0)
	{
		return (newError(file->fullpath, strerror(errno)));
	}
	if (result > 0)
	{
		file->hasACL = 1;
	}
	return (noErrors());
}

static int	readFileLstat(t_file *file)
{
	if (lstat(file->fullpath, &(file->stat)) != 0)
	{
		file->accessErrno = errno;
		return (-1);
	}
	return (0);
}

/*
**	Считываю стандартные аттрибуты файла
**	обрабатываю полученные результаты
**	если файл - устройство, то вычисляю мажор и минор id
**	если файл - символическая ссылка, определяю на что она ссылается
**	считываю имена автора и группы
**	по ID полученным из аттрибутов, считываю расширенные аттрибуты, если
**	они существуют - помечаю у файла их наличие
*/

t_error	readHandleFileAttributes(t_file *file)
{
	t_error	error;

	if (readFileLstat(file))
		return (noErrors());
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
	error = readFileACL(file);
	if (error.wasSet)
		return (error);
	return (noErrors());
}
