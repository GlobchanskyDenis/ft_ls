#!/bin/bash

## Тут только простые тесты флагов влияющих только на количество
##	информации о файле и на фильтр самих файлов

##	Проверка последнего вывода
# head ../myOut.txt ; echo "" ; head ../origOut.txt

## Сначала установим локаль (это необходимо для всех OS кроме MacOS
##	- по идее на ней это стоит по умолчанию). Без нее стандартная ls
##	будет сортировать по имени неправильно
export LC_ALL=C

echo "   Тест одиночных флагов"

## Флаг отображающий все имена файлов разделяя их EOL
echo "   01) ls -1   (flag  -1   & no file args)"
./ft_ls -1 > ../myOut.txt
ls -1 > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаг отображающий имена файлов, права доступа,
##	имена автора и группы, вес файла, количество жестких
##	ссылок разделяя их EOL
echo "   02) ls -l   (flag  -l   & no file args)"
./ft_ls -l > ../myOut.txt
ls -l > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Добавлен флаг показывающий скрытые файлы
echo "   03) ls -la  (flags -la  & no file args)"
./ft_ls -la > ../myOut.txt
ls -la > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Добавлен флаг показывающий только текущую папку
echo "   04) ls -ld  (flags -ld  & no file args)"
./ft_ls -ld > ../myOut.txt
ls -ld > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Только флаг показывающий только текущую папку
echo "   05) ls -d   (flag  -d   & no file args)"
./ft_ls -d > ../myOut.txt
ls -d > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Добавлены флаги показывающие только текущую папку и скрытые файлы
echo "   06) ls -lad (flags -lad & no file args)"
./ft_ls -lad > ../myOut.txt
ls -lad > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаг отображающий имена файлов, права доступа,
##	имя группы, вес файла, количество жестких
##	ссылок разделяя их EOL
echo "   07) ls -g   (flag  -g   & no file args)"
./ft_ls -g > ../myOut.txt
ls -g > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   Тест взаимоисключающих флагов из этой же группы"

## Флаг g повторяет поведение l, но без колонки имени автора
echo "   11) ls -gl  (flags -gl can conflict)"
./ft_ls -gl > ../myOut.txt
ls -gl > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Предыдущий тест в обратном порядке флагов
echo "   12) ls -lg  (flags -lg can conflict)"
./ft_ls -lg > ../myOut.txt
ls -lg > ../origOut.txt
cmp ../myOut.txt ../origOut.txt
