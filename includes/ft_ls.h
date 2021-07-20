#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/libft.h"

/*	For all  */

# include <sys/types.h>

/*	For lstat, opendir, ctime, getpwuid, getgrgid, errno  */

# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>

/*
**	Тут описываю типы файлов, которые могут встретится
*/

# define UNKNOWN					0
# define SOCKET						2
# define DIRECTORY					4
# define BLOCK_DEV					6
# define FILE						8
# define SYMBOLIC					10

/*
**	Тут описываю флаги, которые обрабатываю
*/

# define FLAG_L						0
# define FLAG_R						1
# define FLAG_RR					2
# define FLAG_A						3
# define FLAG_T						4
# define FLAG_U						5
# define FLAG_F						6
# define FLAG_G						7
# define FLAG_D						8
# define FLAG_1						9
# define FLAG_COLOR					10
# define FLAG_HELP					11
# define FLAG_FILE_ARGS				12

# define SORT_BY_NAME				14
# define SORT_BY_ACCESS				15
# define SORT_BY_MODIF				16
# define SHOW_ACCESS_TIME			17
# define SHOW_MODIF_TIME			18
# define SEPARATOR_EOL				19
# define SHOW_RIGHTS_GROUP_WEIGHT	20
# define SHOW_AUTHOR				21
# define SHOW_HIDDEN				22
# define DISABLE_QUOTES				23

/*	Это костыль связанный с говноархитектурой
**	Школа 42 - сделайте демократичную норму кода!!  */

# define SEPARATOR_FOLDERS_EOL		24

/*	Константы escape последовательностей  */

# define COLOR_MODE					"\033[35m"
# define COLOR_AUTHOR				"\033[36m"
# define COLOR_NAME					"\033[34m"
# define NO_COLOR					"\033[m"

/*	Константа описывающая максимальную длинну имени
**	под которую я буду выделять память в стеке функции
**	или как строковую переменную в составе структуры  */

# define MAX_FILENAME				255
# define MAX_DEVICESIZE				60
# define START_BUF_SIZE				100000

/*
**	ТИПЫ ДАННЫХ
*/

/*	Структура, описывающая метаинформацию файла или папки
**	Данная структура входит в состав данных структуры файла
**	Используется в основном для отображения информации о
**	файле при включенном флаге -l -- максимальная ширина
**	каждой колонки и так далее  */

typedef struct s_meta
{
	size_t	blocksNum;
	size_t	hasACL;
	size_t	maxLinksNumLen;
	size_t	maxAuthorLen;
	size_t	maxGroupLen;
	size_t	maxSizeLen;
	size_t	maxMajorLen;
	size_t	maxMinorLen;
	size_t	sum;
	size_t	oneOfFilesNeedsQuotes;
}	t_meta;

/*	Ключевая структура проекта - файл  */

typedef struct s_file
{
	char			name[MAX_FILENAME + 1];
	char			alterName[MAX_FILENAME + 1];
	char			*fullpath;
	char			*symlink;
	char			author[MAX_FILENAME + 1];
	char			group[MAX_FILENAME + 1];
	char			devId[MAX_DEVICESIZE + 1];
	int				accessErrno;
	int				isNeedNameQuotes;
	int				isNeedPathQuotes;
	int				isArgument;
	int				hasACL;
	int				type;
	t_meta			meta;
	struct stat		stat;
	struct s_file	*child;
	struct s_file	*next;
}	t_file;

/*	Структура ошибки. В проекте реализована обработка
**	ошибок. Везде где можно обработать ошибку функция
**	возвращает данную структуру (в стеке). За признак
**	того, что произошла ошибка отвечает флаг wasSet.
**	Также имеет в своем составе информацию, которая позво-
**	ляет идентифицировать - что произошло и обработать
**	эту ошибку в главной функции проекта. Благодаря данному
**	подходу в проекте не используется функция exit()  */

typedef struct s_error
{
	int			wasSet;
	char		*panic;
	char const	*access;
	char		option;
	int			errNo;
}	t_error;

/*
**	ПРОТОТИПЫ ФУНКЦИЙ РАСБРОСАННЫХ ПО ФАЙЛАМ
*/

/*	alternate.c  */

int		initAlternateString(char *dst, char *src, int flags);

/*	directory.c  */

t_error	readDirFiles(int flags, t_file *directory);

/*	directoryHandlers.c  */

int		isDirecoryHasRecursion(t_file *directory);

/*	display_fillBufFileMode.c  */

void	fillBufFileMode(int flags, t_string *buf, t_file *file, t_meta meta);

/*	display.c  */

t_error	displayFileTree(int flags, t_file *head);
t_error	fillBufRecurs(int flags, t_string *buf, t_file *head, t_meta meta);

/*	displayDirHeader.c  */

t_error	fillBufDirFullpathTotal(int flags, t_string *buf, t_file *dir);
t_error fillBufDirFullpathTotalWithCLICondition(int flags, t_string *buf, \
	t_file *dir, t_file *dirHead);

/*	displayFile.c  */

void	fillBufStartFileMode(int flags, t_string *buf, t_file *file);
t_error	fillBufFile(int flags, t_string *buf, t_file *file, t_meta meta);

/*	dump.c */

void	DumpFlags(int flags);
void	DumpFiles(t_list *files);
void	DumpFileTree(int prefix, t_file *currentFile);
void	DumpBits(int value);

/*	error_constructor.c  */

t_error	newError(char *cause, char *description);
t_error	accessFailed(char const *av, int errNo);
t_error	invalidOption(char c);
t_error	unrecognizedOption(char *argument);
t_error	allocateFailed(void);

/*	error_handler.c  */

int		freeError(t_error error);
int		handleError(t_error error);
t_error	noErrors(void);

/*	file.c  */

t_file	*newFile(char const *name, char *path, int type, int flags);
void	freeFile(t_file **file);
int		isFileNotExist(char const *filename);
int		calcOnlyDirectories(t_file *file);
int		calcOnlyDirectoriesThatWeCanAccess(t_file *file);
int		calcOnlyNotDirectories(t_file *file);

/*	filenameList.c  */

t_error	addToFilenameList(char *filename, t_list **fileList);
int		freeFilenameList(t_list **fileList);

/*	fileTree.c  */

t_error	initializeFileTree(int flags, t_list *files, t_file **fileTree);
int		freeFileTree(t_file **fileTree);

/*	flagsHandle.c flagsParse1.c flagsParse2.c flagsGetters.c  */

int		isFlag(char const *av);
int		isNeedToSkipThisFlag(char const *av);
// t_error	handleShortFlag(const char c, int *flags);
t_error	parseShortFlags(const char *av, int *flags);
t_error	parseCLIArgumentToFlags(const char *av, int *flags);
int		isSortingDisabled(int flags);

/*	flagsSetSort.c  */

int 	setSortByName(int flags);
int 	setSortByModification(int flags);
int 	setSortByAccess(int flags);
int		setSortDisable(int flags);

/*	flagsSetters1.c flagsSetters2.c flagsSetters3.c  */

int		setFlagLong(int flags);
int		setFlagInColumn(int flags);
int		setFlagLongWithoutAuthor(int flags);
int		setFlagHiddenA(int flags);
int		setFlagOnlyDirectories(int flags);
int		setFlagReverse(int flags);
int		setFlagRecursion(int flags);
int		setFlagSortByModificationTime(int flags);
int		setFlagSortByAccessTime(int flags);
int		setFlagDisableSort(int flags);

/*	insert.c  */

void	insertByFlags(int flags, t_file *dir, t_file *newfile);

/*	insertByAccessTime.c  */

int		insertByAccessTime(t_file *dir, t_file *prev, t_file *next, \
	t_file *node);
int		insertByAccessTimeReverse(t_file *dir, t_file *prev, t_file *next, \
	t_file *node);

/*	insertByModTime.c  */

// int		insertByModTime(t_file *dir, t_file *prev, t_file *next, t_file *newfile);
// int		insertByModTimeReverse(t_file *dir, t_file *prev, t_file *next, t_file *newfile);

int		insertByModTimeNameDesc(t_file *dir, t_file *prev, t_file *next, \
	t_file *node);
int		insertByModTimeReverseNameDesc(t_file *dir, t_file *prev, \
	t_file *next, t_file *node);
int		insertByModTimeNameAsc(t_file *dir, t_file *prev, t_file *next, \
	t_file *node);
int		insertByModTimeReverseNameAsc(t_file *dir, t_file *prev, \
	t_file *next, t_file *node);
int	insertByModTimeInodeDescNameDesc(t_file *dir, t_file *prev, t_file *next,
		t_file *newfile);

/*	insertByName.c  */

int		insertByName(t_file *dir, t_file *prev, t_file *next, t_file *node);
int		insertByNameReverse(t_file *dir, t_file *prev, t_file *next, \
	t_file *node);

/*	insertHandlers  */

int		insertNewFileAsFirstInFolder(t_file *dir, t_file *newfile);
int		insertNewFileBetweenPrevAndNext(t_file *prev, t_file *next, t_file \
	*newfile);
int		insertNewFileAsLastInFolder(t_file *prev, t_file *newfile);

/*	insertWithoutOrder.c  */

int		insertWithoutOrder(t_file *dir, t_file *prev, t_file *next, \
	t_file *node);

/*	lstat.c  */

t_error	readHandleFileAttributes(t_file *file);

/*	majorMinor.c  */
t_meta	calcDeviceMajorMinorLength(t_file *file);
void	fillBufByFileSizeColumn(t_string *buf, t_file *file, t_meta meta);

/*	meta.c  */

t_meta	calcMetaOnlyFromFiles(t_file *file);
void	metaExchange(t_file *dir, t_file *newfile);

/*	reader.c  */

t_error	reader(int ac, char **av, int *flags, t_list **filenames);
void	printUsage(void);

#endif
