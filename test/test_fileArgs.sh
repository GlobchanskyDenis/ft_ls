#!/bin/bash

## Тут тесты отображения различных комбинаций списка файлов заданного из CLI

## ВАЖНО!! Требуется папка test содержащая некоторое количество файлов
##	и папок для рекурсивного отображения

##	Проверка последнего вывода
# head ../myOut.txt ; echo "" ; head ../origOut.txt

## Сначала установим локаль (это необходимо для всех OS кроме MacOS
##	- по идее на ней это стоит по умолчанию). Без нее стандартная ls
##	будет сортировать по имени неправильно
export LC_ALL=C

echo "   Тест одиночных флагов"

echo "   01) ls Makefile  (no flags & one file arg)"
./ft_ls Makefile > ../myOut.txt
ls Makefile > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   02) ls src/main.c  (no flags & one file arg)"
./ft_ls src/main.c > ../myOut.txt
ls src/main.c > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   03) ls -1 src/main.c src/lstat.c  (flag -1 & two file arg)"
./ft_ls -1 src/main.c src/lstat.c > ../myOut.txt
ls -1 src/main.c src/lstat.c > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   04) ls -1 Makefile .gitignore  (flag -1 & two file arg (one of them is hidden))"
./ft_ls -1 Makefile .gitignore > ../myOut.txt
ls -1 Makefile .gitignore > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   05) ls -1 .gitignore Makefile (flag -1 & two file arg (another order))"
./ft_ls -1 .gitignore Makefile > ../myOut.txt
ls -1 .gitignore Makefile > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   06) ls -1 src/*.o (flag -1 & many file args)"
./ft_ls -1 src/*.o > ../myOut.txt
ls -1 src/*.o > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   07) ls -1 src (flag -1 & one directory as argument)"
./ft_ls -1 src > ../myOut.txt
ls -1 src > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   08) ls -1 src/ (flag -1 & one directory as argument)"
./ft_ls -1 src/ > ../myOut.txt
ls -1 src/ > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   09) ls -1 includes src (flag -1 & two directories as argument)"
./ft_ls -1 includes src > ../myOut.txt
ls -1 includes src > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   11) ls -1 src includes (flag -1 & two directories as argument (another order))"
./ft_ls -1 src includes > ../myOut.txt
ls -1 src includes > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   12) ls -1 . (flag -1 & current dirrectory as argument)"
./ft_ls -1 . > ../myOut.txt
ls -1 . > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   13) ls -1 / (flag -1 & root dirrectory as argument)"
./ft_ls -1 / > ../myOut.txt
ls -1 / > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   14) ls -1 NOT_EXISTING_FILE (flag -1 & not existing file as argument)"
./ft_ls -1 NOT_EXISTING_FILE  1> ../myOut.txt    2> ../myErrOut.txt
ls      -1 NOT_EXISTING_FILE  1> ../origOut.txt  2> ../origErrOut.txt
cmp ../myOut.txt    ../origOut.txt
cmp ../myErrOut.txt ../origErrOut.txt

echo "   15) ls -1 Makefile NOT_EXISTING_FILE (flag -1 & existing and not existing file as argument)"
./ft_ls -1 Makefile NOT_EXISTING_FILE  1> ../myOut.txt    2> ../myErrOut.txt
ls      -1 Makefile NOT_EXISTING_FILE  1> ../origOut.txt  2> ../origErrOut.txt
cmp ../myOut.txt    ../origOut.txt
cmp ../myErrOut.txt ../origErrOut.txt

echo "   16) ls -1 Makefile src (flag -1 & file and folder as arguments)"
./ft_ls -1 Makefile src > ../myOut.txt
ls -1 Makefile src > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   17) ls -1 src Makefile (flag -1 & file and folder as arguments (another order))"
./ft_ls -1 src Makefile > ../myOut.txt
ls -1 src Makefile > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   18) ls -1 src/f* Makefile (flag -1 & file and some files in another folder as arguments)"
./ft_ls -1 src/f* Makefile > ../myOut.txt
ls -1 src/f* Makefile > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   19) ls -1 Makefile src/f* (flag -1 & file and some files in another folder as arguments (another order))"
./ft_ls -1 Makefile src/f* > ../myOut.txt
ls -1 Makefile src/f* > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   20) ls -l Makefile src/file.c includes/ft_ls.h (flag -l & three files in different folders as argument)"
./ft_ls -l Makefile src/file.c includes/ft_ls.h > ../myOut.txt
ls -l Makefile src/file.c includes/ft_ls.h > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   21) ls -l /dev/ (flag -l & directory /dev/ has not only files but devices too)"
./ft_ls -l /dev/ > ../myOut.txt
ls -l /dev/ > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   22) ls -lR ./test (flag -l & recursively directory test)"
./ft_ls -lR ./test > ../myOut.txt
ls -lR ./test > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   23) ls -ld ./test (flags -ld)"
./ft_ls -ld ./test > ../myOut.txt
ls -ld ./test > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   24) ls -ld (flags -ld)"
./ft_ls -ld > ../myOut.txt
ls -ld > ../origOut.txt
cmp ../myOut.txt ../origOut.txt
