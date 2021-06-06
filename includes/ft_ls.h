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
# include <sys/types.h>
# include <sys/xattr.h>

# define UNKNOWN					0
# define SOCKET						2
# define DIRECTORY					4
# define BLOCK_DEV					6
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
# define FLAG_1						(1 << 9)
# define FLAG_COLOR					(1 << 10)
# define FLAG_HELP					(1 << 11)
# define FLAG_FILE_ARGS				(1 << 12)
# define COLOR_MODE					"\033[35m"
# define COLOR_AUTHOR				"\033[36m"
# define COLOR_NAME					"\033[34m"
# define NO_COLOR					"\033[m"
# define MAX_FILENAME				255

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct		s_meta
{
	size_t			blocksNum;
	size_t			hasACL;
	size_t			maxLinksNumLen;
	size_t			maxAuthorLen;
	size_t			maxGroupLen;
	size_t			maxSizeLen;
	size_t			sum;
}					t_meta;

typedef	struct		s_file
{
	char			*name;
	char			*alterName;
	char			*fullpath;
	char			*symlink;
	char			author[MAX_FILENAME + 1];
	char			group[MAX_FILENAME + 1];
	int				accessErrno;
	int				isNeedQuotes;
	int				isArgument;
	int				hasACL;
	int				type;
	t_meta			meta;
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
	int				errNo;
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
**	display.c
*/
t_error	displayFileTree(int flags, t_file *head);

/*
**	displayFile.c
*/
void	fillBufFileMode(int flags, t_string *buf, t_file *file, t_meta meta);
void	fillFileAuthor(int flags, t_string *buf, t_file *file, \
		t_meta meta);
t_error	fillFileTime(int flags, t_string *buf, t_file *file);
t_error	fillFileName(int flags, t_string *buf, t_file *file);

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
t_error accessFailed(char const *av, int errNo);
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
t_file	*newFile(char const *name, char *path, int type);
// t_error	createChildFilePath(t_file *directory, char **path);
void	freeFile(t_file **file);

/*
**	filenameList.c
*/
t_error	addToFilenameList(char *filename, t_list **fileList);
int		freeFilenameList(t_list **fileList);

/*
**	fileTree.c
*/
t_error	initializeFileTree(int flags, t_list *files, t_file **fileTree);
int		freeFileTree(t_file **fileTree);

/*
**	insert.c
*/
void	insertByFlags(int flags, t_file *dir, t_file *newfile);

/*
**	insertByAccessTime.c
*/
int		insertByAccessTime(t_file *dir, t_file *prev, t_file *next,
		t_file *node);
int		insertByAccessTimeReverse(t_file *dir, t_file *prev, t_file *next,
		t_file *node);

/*
**	insertByModTime.c
*/
int		insertByModTime(t_file *dir, t_file *prev, t_file *next, t_file *node);
int		insertByModTimeReverse(t_file *dir, t_file *prev, t_file *next,
		t_file *node);

/*
**	insertByName.c
*/
int		insertByName(t_file *dir, t_file *prev, t_file *next, t_file *node);
int		insertByNameReverse(t_file *dir, t_file *prev, t_file *next,
		t_file *node);

/*
**	insertWithoutOrder.c
*/
int		insertWithoutOrder(t_file *dir, t_file *prev, t_file *next,
		t_file *node);


/*
**	lstat.c
*/
int		isFileNotExist(char const *filename);
t_error	readHandleFileAttributes(t_file *file);

/*
**	parseFlags.c
*/
t_error	parseFlags(const char *av, int *flags);
// t_error checkFlags(const char c);
// t_error	checkForLongFlag(char const *av);
// void	parseShortFlags(const char *av, int *flags);
// void	parseLongFlag(const char *av, int *flags);

/*
**	reader.c
*/
t_error	checkForErrors(char const *av);
t_error	reader(int ac, char **av, int *flags, t_list **filenames);
void	printUsage();

#endif

