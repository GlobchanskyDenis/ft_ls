#include "ft_ls.h"

void	DumpFlags(int flags)
{
	fprint("--- Dump flags ---\n");
	if (flags & FLAG_L)
		fprint("flag 'l' -- use a long listing format\n");
	if (flags & FLAG_R)
		fprint("flag 'r' -- reverse order while sorting\n");
	if (flags & FLAG_A)
		fprint("flag 'a' -- show hidden .\n");
	if (flags & FLAG_RR)
		fprint("flag 'R' -- list subdirectories recursively\n");
	if (flags & FLAG_T)
		fprint("flag 't' -- sort by modification time, newest first\n");
	if (flags & FLAG_U)
		fprint("flag 'u' -- sort by, and show, access time\n");
	if (flags & FLAG_F)
		fprint("flag 'f' -- disable sorting\n");
	if (flags & FLAG_G)
		fprint("flag 'g' -- like -l, but do not list owner\n");
	if (flags & FLAG_D)
		fprint("flag 'd' -- list directories, not content\n");
	if (flags & FLAG_COLOR)
		fprint("flag '--color' -- display in color\n");
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
	fprint("%s\t", (file->name == NULL) ? "NULL" : file->name);
	fprint("%s\t", (file->path == NULL) ? "NULL" : file->path);
	fprint("%s\t", (file->type == DIRECTORY) ? "DIR" : (
		(file->type == FILE) ? "FILE" : (
		(file->type == SYMBOLIC) ? "SYMLINK" : "NOT_SET")));
	DumpBits(file->stat.st_mode);
	fprint("\t%s\t", (file->author == NULL) ? "NULL" : file->author);
	fprint("%s\t", (file->group == NULL) ? "NULL" : file->group);
	fprint("hard_links=%d\n", file->stat.st_nlink);
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