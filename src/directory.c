#include "ft_ls.h"

/*
**	Создает новый файл с путем = путь папки + имя папки и именем
**	далее добавляет новый файл в конец списка дочерних файлов
*/
t_error	*addFileToDirectory(int flags, t_file *directory, char *name, int type)
{
	char	*path;
	t_file	*newfile;
	t_error	*error;

	if (name == NULL)
		return (newError(name));
	if ((error = createChildFilePath(directory, &path)))
		return (error);
	if (!(newfile = newFile(name, path, 1, type)))
	{
		free(path);
		return (newError("malloc returned NULL"));
	}
	if ((flags & FLAG_L) || (flags & FLAG_G) || (flags & FLAG_D))
		fprint("Заглушка\n");	// Через lstat вычислить всю инфу о файле;
		// В случае флага D и файл является папкой - нужно скипнуть файл от добавления
	insertAsChild(directory, newfile);
	return (NULL);
}

t_error	*openDirectory(char *name, DIR **dir)
{
	if (name != NULL)
	{
		if (!(*dir = opendir(name)))
			return (permissionError(name));
	}
	else if (!(*dir = opendir(".")))
		return (permissionError("."));
	return (NULL);
}

int		isNeedToSkipFile(int flags, char *filename)
{
	if (!ft_strncmp(filename, ".", 1) && !(flags & FLAG_A) &&
		!(flags & FLAG_G))
		return (1);
	return (0);
}

t_error	*readDirFiles(int flags, t_file *directory)
{
	DIR			*dir;
	t_dirent	*entry;
	t_error		*error;

	if ((error = openDirectory(directory->name, &dir)))
		return (error);
	while ( (entry = readdir(dir)) != NULL)
	{
		if (isNeedToSkipFile(flags, entry->d_name))
			continue ;
		if ((error = addFileToDirectory(flags, directory, entry->d_name,
			entry->d_type)) != NULL)
		{
			closedir(dir);
			return (error);
		}
		// fprint("%s [%d]\n", entry->d_name, entry->d_type);
    }
	closedir(dir);
	return (NULL);
}