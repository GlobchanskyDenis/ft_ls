#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"

/*
**	For lstat
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

/*
**	For opendir
*/
// #include <sys/types.h>
# include <dirent.h>

# define UNKNOWN					0
# define DIRECTORY					4
# define FILE						8
# define FLAG_L						(1 << 0)
# define FLAG_R						(1 << 1)
# define FLAG_RR					(1 << 2)
# define FLAG_A						(1 << 3)
# define FLAG_T						(1 << 4)
# define FLAG_U						(1 << 5)
# define FLAG_F						(1 << 6)
# define FLAG_G						(1 << 7)
# define FLAG_D						(1 << 8)
# define FLAG_COLOR					(1 << 9)

typedef	struct		s_file
{
	char			*name;
	char			*path;
	t_string		*pathName;
	t_string		*author;
	t_string		*group;
	t_string		*time;
	int				permissionDenied;
	int				isDir;
	int				weight;
	int				mode;
	struct s_file	*child;
	struct s_file	*next;
}					t_file;

typedef struct      s_error
{
	char			*panic;
	char const		*access;
	char			option;
	char			*permission;
}					t_error;

typedef struct stat t_stat;
typedef struct dirent t_dirent;

/*
**	directory.c
*/
t_error	*readDirFiles(int flags, t_file *directory);

/*
**	dump.c
*/
void	DumpFlags(int flags);
void	DumpFiles(t_list *files);
void	DumpFileTree(int prefix, t_file *currentFile);
void	DumpBits(int value);

/*
**	error_constructor.c
*/
t_error	*newError(char *newPanic);
t_error *accessFailed(char const *av);
t_error *invalidOption(char c);
t_error	*emptyError();
t_error *permissionError(char const *fileName);

/*
**	error_handler.c
*/
int		freeError(t_error *error);
int		handleError(t_error *error);

/*
**	file.c
*/
t_file	*newFile(char const *name, char const *path,
	int isNeedToAllocateName, int type);
t_error	*createChildFilePath(t_file *directory, char **path);
void	insertAsChild(t_file *directory, t_file *newfile);
void	insertAsNext(t_file *headFile, t_file *newfile);
void	freeFile(t_file **file);

/*
**	filenameList.c
*/
t_error	*addToFilenameList(char *filename, t_list **fileList);
int		freeFilenameList(t_list **fileList);

/*
**	fileTree.c
*/
t_error	*initializeFileTree(int flags, t_list **files, t_file **fileTree);
void	freeFileTree(t_file **fileTree);

/*
**	lstat.c
*/
int		isFileExist(char const *filename);
t_error	*readFileLstat(t_file *file);

/*
**	parseFlags.c
*/
t_error	*parseFlags(const char *av, int *flags);
t_error *checkFlags(const char c);
t_error	*checkForLongFlag(char const *av);
void	parseShortFlags(const char *av, int *flags);
void	parseLongFlag(const char *av, int *flags);

/*
**	reader.c
*/
t_error	*checkForErrors(char const *av);
t_error	*reader(int ac, char **av, int *flags, t_list **filenames);
void	printUsage();

#endif