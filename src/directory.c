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

	if (name == NULL)
		return (newError(name));
	error = createChildFilePath(directory, &path);
	if (error.wasSet)
		return (error);
	if (!(newfile = newFile(name, path, type)))
	{
		free(path);
		return (allocateFailed());
	}
	if ((flags & FLAG_L) || (flags & FLAG_G) || (flags & FLAG_D))
	{
		error = readFileLstat(newfile);
		if (error.wasSet)
			return (error);
	}
	// Через lstat вычислить всю инфу о файле;
	// В случае флага D и файл не является папкой - нужно скипнуть файл от добавления
	insertAsChild(directory, newfile);
	if ((flags & FLAG_RR) && (type == DIRECTORY))
	{
		error = readDirFiles(flags, newfile);
		if (error.wasSet)
			return (error);
	}

	return (noErrors());
}

t_error	openDirectory(t_file *directory, DIR **dir)
{
	char	fullPath[1024];
	size_t	nameLen;
	size_t	pathLen;
	char	*buf;

	if (directory->name == NULL)
	{
		if (!(*dir = opendir(".")))
		{
			directory->permissionDenied = 1;
			return (noErrors());
		}
	}
	else if (directory->path == NULL)
	{
		if (!(*dir = opendir(directory->name)))
		{
			directory->permissionDenied = 1;
			return (noErrors());
		}
	}
	else {
		nameLen = ft_strlen(directory->name);
		pathLen = ft_strlen(directory->path);
		if (nameLen + pathLen < 1022)
		{
			ft_strcpy(fullPath, directory->path);
			ft_strcpy(&(fullPath[pathLen]), "/");
			ft_strcpy(&(fullPath[pathLen + 1]), directory->name);
			fullPath[nameLen + 1 + pathLen] = '\0';
			fprint("concatinated fullPath %s\n", fullPath);
			if (!(*dir = opendir(fullPath)))
			{
				directory->permissionDenied = 1;
				return (noErrors());
			}
		} else {
			if (!(buf = ft_concat3(directory->path, "/", directory->name)))
				return (allocateFailed());
			fprint("concatinated buf %s\n", buf);
			if (!(*dir = opendir(buf)))
			{
				directory->permissionDenied = 1;
				free(buf);
				return (noErrors());
			}
			free(buf);
		}
	}
	return (noErrors());
}

int		isNeedToSkipFile(int flags, char *filename)
{
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

	fprint("read dir files '%s'/'%s'\n", (directory->path == NULL) ? "NULL" : directory->path, (directory->name == NULL) ? "NULL" : directory->name);
	error = openDirectory(directory, &dir);
	fprint("%s\n", (directory->permissionDenied) ? "permission Denied" : "success");
	if (error.wasSet)
		return (error);
	if (directory->permissionDenied)
		return (noErrors());
	while ((entry = readdir(dir)) != NULL)
	{
		// fprint("%s [%d]\n", entry->d_name, entry->d_type);
		if (isNeedToSkipFile(flags, entry->d_name))
			continue ;
		error = addFileToDirectory(flags, directory, entry->d_name, entry->d_type);
		if (error.wasSet)
		{
			closedir(dir);
			return (error);
		}
		// fprint("%s [%d]\n", entry->d_name, entry->d_type);
    }
	closedir(dir);
	return (noErrors());
}