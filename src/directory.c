#include "ft_ls.h"

/*
**	Создает новый файл с путем = путь папки + имя папки и именем
**	далее добавляет новый файл в конец списка дочерних файлов
*/
t_error	addFileToDirectory(int flags, t_file *directory, char *name, int type)
{
	char	*path;
	t_file	*newfile;
	t_error	error;

	if ((error = createChildFilePath(directory, &path)).wasSet)
		return (error);
	if (!(newfile = newFile(name, path, type)))
	{
		free(path);
		return (allocateFailed());
	}
	if ((flags & FLAG_L) || (flags & FLAG_G) || (flags & FLAG_D))
	{
		if ((error = readFileLstat(newfile)).wasSet)
			return (error);
	}
	insertToChildsByFlags(flags, directory, newfile);
	// insertAsChild(directory, newfile);
	if ((flags & FLAG_RR) && (type == DIRECTORY))
	{
		if ((error = readDirFiles(flags, newfile)).wasSet)
			return (error);
	}
	return (noErrors());
}

t_error openDirectoryWithPath(t_file *directory, DIR **dir)
{
	char	fullPath[1024];
	char	*buf;

	if (ft_strlen(directory->name) + ft_strlen(directory->path) < 1022)
	{
		ft_bufconcat3(fullPath, directory->path, "/", directory->name);
		if (!(*dir = opendir(fullPath)))
			directory->permissionDenied = 1;
	} else {
		if (!(buf = ft_concat3(directory->path, "/", directory->name)))
			return (allocateFailed());
		if (!(*dir = opendir(buf)))
			directory->permissionDenied = 1;
		free(buf);
	}
	return (noErrors());
}

t_error	openDirectory(t_file *directory, DIR **dir)
{
	if (directory->name == NULL)
	{
		if (!(*dir = opendir(".")))
			directory->permissionDenied = 1;
	}
	else if (directory->path == NULL)
	{
		if (!(*dir = opendir(directory->name)))
			directory->permissionDenied = 1;
	}
	else
		return (openDirectoryWithPath(directory, dir));
	return (noErrors());
}

int		isNeedToSkipFile(int flags, char *filename)
{
	if (filename == NULL)
		return (1);
	if (!ft_strncmp(filename, ".", 1) && !(flags & FLAG_A) &&
		!(flags & FLAG_G))
		return (1);
	return (0);
}

t_error	readDirFiles(int flags, t_file *directory)
{
	DIR			*dir;
	t_dirent	*entry;
	t_error		error;

	error = openDirectory(directory, &dir);
	if (error.wasSet)
		return (error);
	if (directory->permissionDenied)
		return (noErrors());
	while ((entry = readdir(dir)) != NULL)
	{
		// fprint("%s [%d]\n", entry->d_name, entry->d_type);
		if (isNeedToSkipFile(flags, entry->d_name))
			continue ;
		error = addFileToDirectory(flags, directory, entry->d_name,
				entry->d_type);
		if (error.wasSet)
		{
			closedir(dir);
			return (error);
		}
    }
	closedir(dir);
	return (noErrors());
}

