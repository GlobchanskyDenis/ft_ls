#include "ft_ls.h"

static char	*allocateFileFullpath(char *dirFullpath, char *name)
{
	char	*dst;
	size_t	pathLen;

	pathLen = ft_strlen(dirFullpath);
	if (pathLen > 0 && dirFullpath[pathLen - 1] == '/')
		pathLen--;
	dst = (char *)malloc(pathLen + ft_strlen(name) + 2);
	if (!dst)
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
**	TODO - TOO MANY LINES
*/

// {
// 		error = readDirFiles(flags, newfile);
// 		if (error.wasSet)
// 			return (error);
// 	}

static t_error	addFileToDirectory(int flags, t_file *directory,
	char *name, int type)
{
	char	*fullpath;
	t_file	*newfile;
	t_error	error;

	fullpath = allocateFileFullpath(directory->fullpath, name);
	if (!fullpath)
		return (allocateFailed());
	newfile = newFile(name, fullpath, type);
	if (!newfile)
	{
		free(fullpath);
		return (allocateFailed());
	}
	if ((flags & (1 << FLAG_L)) || (flags & (1 << FLAG_G)) || (flags & (1 << \
		FLAG_D)) || (flags & (1 << FLAG_T)) || (flags & (1 << FLAG_U)))
	{
		error = readHandleFileAttributes(newfile);
		if (error.wasSet)
			return (error);
	}
	insertByFlags(flags, directory, newfile);
	if ((flags & (1 << FLAG_RR)) && (type == DIRECTORY) && \
		(ft_strcmp(newfile->name, ".")) && (ft_strcmp(newfile->name, "..")))
		return (readDirFiles(flags, newfile));
	return (noErrors());
}

/*
**	If the file does not need to be output, I will not add it
**	to the file list
*/

static int	isNeedToSkipFile(int flags, char *filename)
{
	if (filename == NULL)
		return (1);
	if (!ft_strncmp(filename, ".", 1) && !(flags & (1 << FLAG_A)) && \
		!(flags & (1 << FLAG_G)))
		return (1);
	return (0);
}

static struct dirent	*readDirrectory(DIR *dir, struct dirent **entry)
{
	*entry = readdir(dir);
	return (*entry);
}

/*
**	Function can fall in recursion (addFileToDirectory function
**	call that in case of recursion flag calls current function)
*/

// entry = readdir(dir); // Кажется эт строку тоже надо закомментить
// while (entry != NULL)

t_error	readDirFiles(int flags, t_file *directory)
{
	DIR				*dir;
	struct dirent	*entry;
	t_error			error;

	// fprint("reading files in %s (%s) directory\n", directory->name, directory->fullpath);
	dir = opendir(directory->fullpath);
	if (!dir)
	{
		// fprint("Marker 1\n");
		directory->accessErrno = errno;
		return (noErrors());
	}
	while (readDirrectory(dir, &entry))
	{
		if (isNeedToSkipFile(flags, entry->d_name))
			continue ;
		error = addFileToDirectory(flags, directory, entry->d_name,
				entry->d_type);
		if (error.wasSet)
		{
			// fprint("Marker 2\n");
			closedir(dir);
			return (error);
		}
	}
	closedir(dir);
	return (noErrors());
}
