#include "ft_ls.h"

/*	Извлекает метаинформацию о ширине колонок (размер файла для файлов,
**	мажор и минор для устройств) для корректных
**	отступов при включенном флаге L
**	Извлечение по принципу - если у файла параметр больше - копируем
**	в мету папки  */

static t_meta	extractSizeFileMetaToDirMeta(t_meta dirMeta, t_file *file)
{
	size_t	length;
	t_meta	fileMeta;

	if (file->stat.st_size == 0 && file->stat.st_rdev != 0)
	{
		fileMeta = calcDeviceMajorMinorLength(file);
		if (fileMeta.maxMajorLen > dirMeta.maxMajorLen)
			dirMeta.maxMajorLen = fileMeta.maxMajorLen;
		if (fileMeta.maxMinorLen > dirMeta.maxMinorLen)
			dirMeta.maxMinorLen = fileMeta.maxMinorLen;
		if (dirMeta.maxMajorLen + 2 + dirMeta.maxMinorLen > \
			dirMeta.maxSizeLen)
			dirMeta.maxSizeLen = dirMeta.maxMajorLen + 2 + \
			dirMeta.maxMinorLen;
	}
	else
	{
		length = countRanksSizeT(file->stat.st_size, 10);
		if (length > dirMeta.maxSizeLen)
			dirMeta.maxSizeLen = length;
	}
	return (dirMeta);
}

/*	Извлекает метаинформацию о ширине колонок (количество блоков,
**	ссылок, длинн имени автора и группы а также флаг - содержит ли
**	файл признак того, имеет ли он признак ACL) для корректных
**	отступов при включенном флаге L
**	Извлечение по принципу - если у файла параметр больше - копируем
**	в мету папки
**	ВЫЗЫВАТЬ СТРОГО ПОСЛЕ extractSizeFileMetaToDirMeta ТАК КАК В
**	ДАННОЙ ФУНКЦИИ СЧИТАЕТСЯ СУММА ВСЕХ ПОЛЕЙ  */

static t_meta	extractNameBlocksFileMetaToDirMeta(t_meta dirMeta, \
	t_file *file)
{
	size_t	length;

	dirMeta.blocksNum += file->stat.st_blocks;
	if (file->hasACL)
		dirMeta.hasACL = 1;
	length = countRanksSizeT(file->stat.st_nlink, 10);
	if (length > dirMeta.maxLinksNumLen)
		dirMeta.maxLinksNumLen = length;
	length = ft_strlen(file->author);
	if (length > dirMeta.maxAuthorLen)
		dirMeta.maxAuthorLen = length;
	length = ft_strlen(file->group);
	if (length > dirMeta.maxGroupLen)
		dirMeta.maxGroupLen = length;
	dirMeta.sum = dirMeta.maxLinksNumLen + dirMeta.maxAuthorLen + \
		dirMeta.maxGroupLen + dirMeta.maxSizeLen + dirMeta.hasACL;
	return (dirMeta);
}

/*	Используется в процессе вывода файлов (из аргументов CLI) в буффер
**	При задании файлов аргументами CLI мы ничего не знаем про то,
**	какие максимальные значения колонок файлов нам встречаются.
**	В данном случае высчитываю мету по факту а не в процессе добавления
**	файла в папку  */

t_meta	calcMetaOnlyFromFiles(t_file *file)
{
	t_meta	meta;

	ft_bzero(&meta, sizeof(t_meta));
	while (file)
	{
		if (file->type != DIRECTORY)
		{
			meta = extractSizeFileMetaToDirMeta(meta, file);
			meta = extractNameBlocksFileMetaToDirMeta(meta, file);
		}
		file = file->next;
	}
	return (meta);
}
