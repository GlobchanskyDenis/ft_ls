#include "ft_ls.h"

/*	Вставляю первым файлом в папку (dir->child)  */

int	insertNewFileAsFirstInFolder(t_file *dir, t_file *newfile)
{
	newfile->next = dir->child;
	dir->child = newfile;
	return (1);
}

/*	Вставляю между prev и next  */

int	insertNewFileBetweenPrevAndNext(t_file *prev, t_file *next, t_file *newfile)
{
	newfile->next = next;
	prev->next = newfile;
	return (1);
}

/*	Next в данном случае будет NULL, поэтому записываю как следующее после
**	prev  */

int	insertNewFileAsLastInFolder(t_file *prev, t_file *newfile)
{
	prev->next = newfile;
	return (1);
}
