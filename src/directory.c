#include "ft_ls.h"

/*
**	Creates a new file with path = folder path + folder name and name
**	then adds a new file to the end of the list of child files.
**	In case of recursion flag - this function goes to recursion
**	(readDirFiles function call that calls current function)
*/

static t_error	addFileToDirectory(int flags, t_file *directory,
	char *name, int type)
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
	if ((flags & FLAG_L) || (flags & FLAG_G) || (flags & FLAG_D) ||
		(flags & FLAG_T) || (flags & FLAG_U))
	{
		if ((error = readFileLstat(newfile)).wasSet)
			return (error);
	}
	insertByFlags(flags, directory, newfile);
	if ((flags & FLAG_RR) && (type == DIRECTORY))
	{
		if ((error = readDirFiles(flags, newfile)).wasSet)
			return (error);
	}
	return (noErrors());
}

static t_error	openDirectory(t_file *directory, DIR **dir)
{
	char	fullPath[1024];
	char	*buf;

	if (directory->path == NULL)
	{
		if (!(*dir = opendir(directory->name)))
			directory->accessErrno = errno;
	}
	else
	{
		if (ft_strlen(directory->name) + ft_strlen(directory->path) < 1022)
		{
			ft_bufconcat3(fullPath, directory->path, "/", directory->name);
			if (!(*dir = opendir(fullPath)))
				directory->accessErrno = errno;
		} else {
			if (!(buf = ft_concat3(directory->path, "/", directory->name)))
				return (allocateFailed());
			if (!(*dir = opendir(buf)))
				directory->accessErrno = errno;
			free(buf);
		}
	}
	return (noErrors());
}

/*
**	If the file does not need to be output, I will not add it
**	to the file list
*/

static int		isNeedToSkipFile(int flags, char *filename)
{
	if (filename == NULL)
		return (1);
	if (!ft_strncmp(filename, ".", 1) && !(flags & FLAG_A) &&
		!(flags & FLAG_G))
		return (1);
	return (0);
}

/*
**	Function can fall in recursion (addFileToDirectory function
**	call that in case of recursion flag calls current function)
*/

t_error			readDirFiles(int flags, t_file *directory)
{
	DIR			*dir;
	t_dirent	*entry;
	t_error		error;

	error = openDirectory(directory, &dir);
	if (error.wasSet)
		return (error);
	if (directory->accessErrno)
		return (noErrors());
	while ((entry = readdir(dir)) != NULL)
	{
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

