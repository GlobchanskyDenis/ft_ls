#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"


/*
**	For all
*/
# include <sys/types.h>

/*
**	For lstat, opendir, ctime, getpwuid, getgrgid, errno
*/
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>

# define UNKNOWN					0
# define DIRECTORY					4
# define FILE						8
# define SYMBOLIC					((1 << 3) | (1 << 1))
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
# define FLAG_HELP					(1 << 10)

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef	struct		s_file
{
	char			*name;
	char			*alterName;
	char			*path;
	char			*symlink;
	char 			*author;
	char 			*group;
	int				permissionDenied;
	int				isNeedQuotes;
	int				type;
	t_stat			stat;
	struct s_file	*child;
	struct s_file	*next;
}					t_file;

typedef struct      s_error
{
	int				wasSet;
	char			*panic;
	char const		*access;
	char			option;
}					t_error;

/*
**		alternate.c
*/
int		initAlternateString(char *dst, char *src);

/*
**	directory.c
*/
t_error	readDirFiles(int flags, t_file *directory);

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
t_error	newError(char *cause, char *description);
t_error accessFailed(char const *av);
t_error invalidOption(char c);
t_error allocateFailed();
t_error noErrors();

/*
**	error_handler.c
*/
int		freeError(t_error *error);
int		handleError(t_error *error);

/*
**	file.c
*/
t_file	*newFile(char const *name, char const *path, int type);
t_error	createChildFilePath(t_file *directory, char **path);
// void	insertAsNext(t_file *headFile, t_file *newfile);
void	insertToNextByFlags(int flags, t_file **head, t_file *newfile);
void	insertToChildsByFlags(int flags, t_file *dir, t_file *newfile);
void	freeFile(t_file **file);

/*
**	filenameList.c
*/
t_error	addToFilenameList(char *filename, t_list **fileList);
int		freeFilenameList(t_list **fileList);

/*
**	fileTree.c
*/
t_error	initializeFileTree(int flags, t_list **files, t_file **fileTree);
void	freeFileTree(t_file **fileTree);

/*
**	lstat.c
*/
int		isFileExist(char const *filename);
t_error	readFileLstat(t_file *file);

/*
**	parseFlags.c
*/
t_error	parseFlags(const char *av, int *flags);
t_error checkFlags(const char c);
t_error	checkForLongFlag(char const *av);
void	parseShortFlags(const char *av, int *flags);
void	parseLongFlag(const char *av, int *flags);

/*
**	reader.c
*/
t_error	checkForErrors(char const *av);
t_error	reader(int ac, char **av, int *flags, t_list **filenames);
void	printUsage();

/*
**	sort.c
*/
int 	insertByName(t_file *dir, t_file *prev, t_file *next, t_file *node);
int 	insertByNameReverse(t_file *dir, t_file *prev, t_file *next, t_file *node);
int 	insertNextByName(t_file **prev, t_file *next, t_file *node);
int 	insertNextByNameReverse(t_file **prev, t_file *next, t_file *node);

#endif