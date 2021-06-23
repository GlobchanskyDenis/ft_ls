#include "ft_ls.h"

/*
**	This file is only for dumping program state in design time
*/

void	DumpFlags(int flags)
{
	fprint("--- Dump flags ---\n");
	if (flags & (1 << FLAG_L))
		fprint("flag 'l' -- use a long listing format\n");
	if (flags & (1 << FLAG_1))
		fprint("flag '1' -- display each file in own line");
	if (flags & (1 << FLAG_R))
		fprint("flag 'r' -- reverse order while sorting\n");
	if (flags & (1 << FLAG_A))
		fprint("flag 'a' -- show hidden .\n");
	if (flags & (1 << FLAG_RR))
		fprint("flag 'R' -- list subdirectories recursively\n");
	if (flags & (1 << FLAG_T))
		fprint("flag 't' -- sort by modification time, newest first\n");
	if (flags & (1 << FLAG_U))
		fprint("flag 'u' -- sort by, and show, access time\n");
	if (flags & (1 << FLAG_F))
		fprint("flag 'f' -- disable sorting\n");
	if (flags & (1 << FLAG_G))
		fprint("flag 'g' -- like -l, but do not list owner\n");
	if (flags & (1 << FLAG_D))
		fprint("flag 'd' -- list directories, not content\n");
	if (flags & (1 << FLAG_COLOR))
		fprint("flag '--color' -- display in color\n");
	if (flags & (1 << FLAG_FILE_ARGS))
		fprint("file names in arguments\n");
	fprint("------------------\n");

}

void	DumpFiles(t_list *files)
{
	fprint("--- Dump files that was in aruments ---\n");
	if (files == NULL)
	{
		fprint("---------------------------------------\n");
		return ;
	}
	while (files != NULL)
	{
		if (files->content == NULL)
			continue ;
		fprint("%s\n", (char *)(files->content));
		files = files->next;
	}
	fprint("---------------------------------------\n");
}

void	DumpFile(int prefix, t_file *file)
{
	while (prefix--)
		fprint("\t");
	fprint("%s\t", file->name);
	if (ft_strlen(file->name) < 8)
		fprint("\t");
	fprint("%s\t", file->fullpath);
	if (ft_strlen(file->fullpath) < 8)
		fprint("\t");

	// fprint("%s\t", (file->alterName == NULL) ? "NULL" : file->alterName);
	// if (file->alterName != NULL)
	// {
	// 	int i = 0;
	// 	while (file->alterName[i])
	// 	{
	// 		fprint("%d.", file->alterName[i]);
	// 		i++;
	// 	}
	// }
	// if (file->name != NULL && file->name[0] < 0)
	// {
	// 	int i = 0;
	// 	while (file->name[i])
	// 		fprint("%d.", (unsigned int)(file->name[i++]));
	// 	fprint("\t");

	// 	i = 0;
	// 	unsigned char *name = (unsigned char *)(file->name);

	// 	while (name[i])
	// 		fprint("%d.", name[i++]);
	// 	fprint("\t");
	// }

	// fprint("%s\t", (file->type == DIRECTORY) ? "DIR" : (
	// 	(file->type == FILE) ? "FILE" : (
	// 	(file->type == SYMBOLIC) ? "SYMLINK" : "NOT_SET")));
	// fprint("%d %d\t", file->accessErrno, file->isNeedQuotes);
	// DumpBits(file->stat.st_mode);

	// fprint("\t%s\t", (file->author == NULL) ? "NULL" : file->author);
	// fprint("%s\t", (file->group == NULL) ? "NULL" : file->group);
	// fprint("hard_links=%d\n", file->stat.st_nlink);

	// fprint("\t%d %d %d %d %d %d ", file->meta.blocksNum, file->meta.maxLinksNumLen, file->meta.maxAuthorLen, file->meta.maxGroupLen,  file->meta.maxSizeLen,   file->meta.sum);

	if (file->meta.blocksNum == 0)
	fprint("\t%d %d %d %d %d %d %d %d %d %d %d %d %d %d ", file->meta.blocksNum, file->stat.st_dev, file->stat.st_ino, file->stat.st_mode,
		file->stat.st_nlink, file->stat.st_uid, file->stat.st_gid, file->stat.st_rdev, file->stat.st_size, file->stat.st_blksize, file->stat.st_blocks,
		file->stat.st_atime, file->stat.st_mtime, file->stat.st_ctime);

	// ssize_t result;
	// char  list[256];
	// ft_bzero(&list, 256);
	// result = listxattr(file->fullpath, list, 255);
	// fprint("'%d %s'", result, list);

	// ft_bzero(&list, 256);
	// result = getxattr(file->fullpath, list, 255);

	fprint("\n");
}

void	DumpFileTree(int prefix, t_file *currentFile)
{
	if (currentFile == NULL)
		return ;
	while (currentFile)
	{
		DumpFile(prefix, currentFile);
		if (currentFile->child != NULL)
			DumpFileTree(prefix + 1, currentFile->child);
		currentFile = currentFile->next;
	}
}

void	DumpBits(int value)
{
	int		i;

	i = 15;
	while (i >= 0)
	{
		if (value & (1 << i))
			fprint("1");
		else
			fprint("0");
		i--;
		if (!((i + 1) % 4))
			fprint(" ");
	}
}

