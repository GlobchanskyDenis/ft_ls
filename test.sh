#!/bin/bash

# это для того, чтобы наверняка локаль соответствовала
export LC_ALL=C

# head ../myOut.txt ; echo "" ; head ../origOut.txt

## Сначала простые варианты - флаги влияющие
##	на количество информации о каждом файле

# Флаг отображающий все имена файлов разделяя их EOL
echo "1) ls -1 (flag -1 & no file args)"
./ft_ls -1 > ../myOut.txt
ls -1 > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# Флаг отображающий имена файлов, права доступа,
#	имена автора и группы, вес файла, количество жестких
#	ссылок разделяя их EOL
echo "2) ls -l (flag -l & no file args)"
./ft_ls -l > ../myOut.txt
ls -l > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# Добавлен флаг показывающий скрытые файлы
echo "3) ls -la (flag -l & no file args)"
./ft_ls -la > ../myOut.txt
ls -la > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# Добавлен флаг показывающий только текущую папку
echo "4) ls -ld (flag -ld & no file args)"
./ft_ls -ld > ../myOut.txt
ls -ld > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# Только флаг показывающий только текущую папку
echo "5) ls -d (flag -d & no file args)"
./ft_ls -d > ../myOut.txt
ls -d > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# Добавлены флаги показывающие только текущую папку и скрытые файлы
echo "6) ls -lad (flag -lad & no file args)"
./ft_ls -lad > ../myOut.txt
ls -lad > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# Флаг отображающий имена файлов, права доступа,
#	имя группы, вес файла, количество жестких
#	ссылок разделяя их EOL
echo "7) ls -g (flag -g & no file args)"
./ft_ls -g > ../myOut.txt
ls -g > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Теперь тестирую флаги влияющие на порядок отображения

# Отображение в обратном порядке
echo "10) ls -lr (flags -lr & no file args)"
./ft_ls -lr > ../myOut.txt
ls -lr > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# сортировка по времени модификации
echo "11) ls -lt (flags -lt & no file args)"
./ft_ls -lt > ../myOut.txt
ls -lt > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# сортировка по времени доступа
echo "12) ls -1t (flags -1t & no file args)"
./ft_ls -1t > ../myOut.txt
ls -1t > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# сортировка по времени доступа + полное отображение
#	(тут должны быть костыли - флаг -l отключает сортировку
#	по времени доступа)
echo "13) ls -lu (flags -lu & no file args)"
./ft_ls -lu > ../myOut.txt
ls -lu > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# сортировка по времени модификации в обратном порядке
echo "14) ls -ltr (flags -ltr & no file args)"
./ft_ls -ltr > ../myOut.txt
ls -ltr > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

# сортировка по времени доступа в обратном порядке
echo "15) ls -lur (flags -lur & no file args)"
./ft_ls -lur > ../myOut.txt
ls -lur > ../origOut.txt
cmp ../myOut.txt ../origOut.txt




# сортировка 
echo "16) ls -1t src (flags -1t & one dir file arg)"
./ft_ls -1t src > ../myOut.txt
ls -1t src > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "17) ls -lt src (flags -lt & one dir file arg)"
./ft_ls -lt src > ../myOut.txt
ls -lt src > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "18) ls -lu src (flags -lu & one dir file arg)"
./ft_ls -lu src > ../myOut.txt
ls -lu src > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

#
echo "19) ls -1 src (flag -1 & one dir file arg)"
./ft_ls -1 src > ../myOut.txt
ls -1 src > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "20) ls -1 . (flag -1 & one dir (.) file arg)"
./ft_ls -1 . > ../myOut.txt
ls -1 . > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "21) ls -1 src/*.o (flag -1 & many files from CLI)"
./ft_ls -1 src/*.o > ../myOut.txt
ls -1 src/*.o > ../origOut.txt
cmp ../myOut.txt ../origOut.txt