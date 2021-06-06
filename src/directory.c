#include "ft_ls.h"

static char	*allocateFileFullpath(char *dirFullpath, char *name)
{
	char	*dst;
	size_t	pathLen;

	pathLen = ft_strlen(dirFullpath);
	if (pathLen > 0 && dirFullpath[pathLen - 1] == '/')
		pathLen--;
	if (!(dst = (char *)malloc(pathLen + ft_strlen(name) + 2)))
		return (NULL);
	ft_strncpy(dst, dirFullpath, pathLen);
	dst[pathLen] = '/';
	ft_strcpy(&(dst[pathLen + 1]), name);
	return (dst);
}

/*
**	Creates a new file with path = folder path + folder name and name
**	then adds a new file to the end of the list of child files.
**	In case of recursion flag - this function goes to recursion
**	(readDirFiles function call that calls current function)
*/

static t_error	addFileToDirectory(int flags, t_file *directory,
	char *name, int type)
{
	char	*fullpath;
	t_file	*newfile;
	t_error	error;

	if (!(fullpath = allocateFileFullpath(directory->fullpath, name)))
		return (allocateFailed());
	if (!(newfile = newFile(name, fullpath, type)))
	{
		free(fullpath);
		return (allocateFailed());
	}
	if ((flags & FLAG_L) || (flags & FLAG_G) || (flags & FLAG_D) ||
		(flags & FLAG_T) || (flags & FLAG_U))
	{
		if ((error = readHandleFileAttributes(newfile)).wasSet)//	readFileLstat
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

	if (!(dir = opendir(directory->fullpath)))
	{
		directory->accessErrno = errno;
		return (noErrors());
	}
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
