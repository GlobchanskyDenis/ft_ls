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

	if ((ret = readlink(file->fullpath, buf, 256)) == -1)
		return (newError(file->fullpath, strerror(errno)));
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
		return (newError(file->fullpath, strerror(errno)));
	if (ft_strlen(pass->pw_name) > MAX_FILENAME)
		return (newError(file->fullpath, "too long author name"));
	ft_strcpy(file->author, pass->pw_name);
	if (!(grp = getgrgid(file->stat.st_gid)))
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
	ssize_t result;
	char list[256];

	result = listxattr(file->fullpath, list, 255);
	if (result < 0)
	{
		return newError(file->fullpath, strerror(errno));
	}
	if (result > 0)
	{
		file->hasACL = 1;
	}
	return (noErrors());
}

static t_error	readFileLstat(t_file *file)
{
	// t_error	error;

	if (lstat(file->fullpath, &(file->stat)) != 0)
	{
		return (newError(file->fullpath, strerror(errno)));
	}
	return (noErrors());
}

/*
**	Считываю стандартные аттрибуты файла, считываю имена автора и группы
**	по ID полученным из аттрибутов, считываю расширенные аттрибуты, если
**	они существуют - помечаю у файла их наличие
*/

t_error		readHandleFileAttributes(t_file *file)
{
	t_error	error;

	// if (!ft_strcmp(file->name, "..")) // В комментарии отправлено в связи с тем, что при выводе может быть сега
	// 	return (noErrors());			 // Осторожнее с этими строками !!!

	// fprint("%s %s\n", file->name, file->fullpath);

	// Считываю lstat
	error = readFileLstat(file);
	if (error.wasSet)
	{
		return (error);
	}

	// обрабатываю полученные результаты
	file->type = file->stat.st_mode >> 12;

	// Считываю куда ссылается символическая ссылка
	if (file->type == SYMBOLIC)
	{
		error = readSymLink(file);
		if (error.wasSet)
		{
			return (error);
		}
	}

	// Считываю имена автора и группы по ID
	error = readAuthorGroupNames(file);
	if (error.wasSet)
	{
		return (error);
	}

	// Считываю расширенное значение аттрибутов
	error = readFileACL(file);
	if (error.wasSet)
	{
		return (error);
	}

	return (noErrors());
}

