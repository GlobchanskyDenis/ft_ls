#include "ft_ls.h"

/*
**	вычислить мажор минор
**	- записать по очереди мажор и минор в строку
**	вычислить длину строки
**	Так как нужно еще выравнивать по столбцам
**	Поэтому тут только высчитываю длинну чисел, которыми
**	впоследствии будут заполнены столбцы
**	+2 это запятая и пробел после нее
*/

t_meta	calcDeviceMajorMinorLength(t_file *file)
{
	size_t	major;
	size_t	minor;
	t_meta	meta;

	major = file->stat.st_rdev >> 8;
	minor = file->stat.st_rdev & 255;
	meta.maxMajorLen = countRanksSizeT(major, 10);
	meta.maxMinorLen = countRanksSizeT(minor, 10);
	meta.maxSizeLen = meta.maxMajorLen + 2 + meta.maxMinorLen;
	return (meta);
}

/*
**	ЗАПОЛНЯЕТ КОЛОНКУ РАЗМЕРА ФАЙЛА ИНФОРМАЦИЕЙ О МАЖОРНОМ И
**	МИНОРНОМ ИДЕНТИФИКАТОРЕ УСТРОЙСТВА.
**	* Проверка является ли файл устройством должна производится до вызова функции.
**	* Проверка, включен ли флаг l, должна производится до вызова функции.
**	* Проверка на вместимость буфера должна производится до вызова функции.
*/

static void	fillBufDeviceMajorMinor(t_string *buf, t_file *file, t_meta meta)
{
	size_t	major;
	size_t	minor;
	int		tab;

	major = file->stat.st_rdev >> 8;
	minor = file->stat.st_rdev & 255;
	tab = (int)meta.maxSizeLen - (int)meta.maxMajorLen - 2 - \
		(int)meta.maxMinorLen;
	while (tab-- > 0)
		stringCat(buf, " ");
	tab = (int)meta.maxMajorLen - (int)countRanksSizeT(major, 10);
	while (tab-- > 0)
		stringCat(buf, " ");
	stringSizeTtoa(buf, major);
	stringCat(buf, ", ");
	tab = (int)meta.maxMinorLen - (int)countRanksSizeT(minor, 10);
	while (tab-- > 0)
		stringCat(buf, " ");
	stringSizeTtoa(buf, minor);
}

/*
**	ЗАПОЛНЯЕТ БУФЕР КОЛОНКОЙ РАЗМЕРА ФАЙЛА.
**	Если это устройство - заполняет мажором и минором
**	Если нет - размером файла
**	* Проверка на вместимость буффера должна производится до вызова функции
**	* Проверка на включенный флаг l должна производится до вызова функции
*/

void	fillBufByFileSizeColumn(t_string *buf, t_file *file, t_meta meta)
{
	if (file->stat.st_size == 0 && file->stat.st_rdev != 0)
	{
		fillBufDeviceMajorMinor(buf, file, meta);
	}
	else
	{
		stringSizeTtoaAlignR(buf, file->stat.st_size, meta.maxSizeLen, ' ');
	}
}
