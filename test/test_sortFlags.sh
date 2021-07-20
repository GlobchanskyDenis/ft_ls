#!/bin/bash

## Тут только тесты флагов сортировки влияющих только порядок файлов при отображении

##	Проверка последнего вывода
# head ../myOut.txt ; echo "" ; head ../origOut.txt

## Сначала установим локаль (это необходимо для всех OS кроме MacOS
##	- по идее на ней это стоит по умолчанию). Без нее стандартная ls
##	будет сортировать по имени неправильно
export LC_ALL=C

echo "   Тест одиночных флагов"

## Файлы в обратном порядке
echo "   01) ls -1r  (flags -1r  & no file args)"
./ft_ls -1r > ../myOut.txt
ls -1r > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Файлы отсортированные по времени модификации начиная с самого нового
echo "   02) ls -1t  (flags -1t  & no file args)"
./ft_ls -1t > ../myOut.txt
ls -1t > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Файлы отсортированные по времени модификации начиная с самого старого
echo "   03) ls -1tr (flags -1tr & no file args)"
./ft_ls -1tr > ../myOut.txt
ls -1tr > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Файлы отсортированные по времени доступа начиная с самого нового
echo "   04) ls -1u  (flags -1u  & no file args)"
./ft_ls -1t > ../myOut.txt
ls -1t > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Файлы отсортированные по времени доступа начиная с самого старого
echo "   05) ls -1ur (flags -1ur & no file args)"
./ft_ls -1tr > ../myOut.txt
ls -1tr > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Отключение сортировки (в порядке, в котором нам отдает его система)
echo "   06) ls -1f  (flags -1f  & no file args)"
./ft_ls -1f > ../myOut.txt
ls -1f > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Отключение сортировки (в обратном порядку, в котором нам отдает его система)
echo "   07) ls -1fr (flags -1fr & no file args)"
./ft_ls -1fr > ../myOut.txt
ls -1fr > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

echo "   Тест взаимоисключающих флагов из этой же группы"

## Флаги сортирующие по времени
echo "   11) ls -lut  (flags -u -t can conflict)"
./ft_ls -lut > ../myOut.txt
ls -lut > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаги сортирующие по времени приведенные в обратном порядке
echo "   12) ls -ltu  (flags -u -t can conflict)"
./ft_ls -ltu > ../myOut.txt
ls -ltu > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаги сортирующие по времени
echo "   13) ls -1ut  (flags -u -t can conflict)"
./ft_ls -1ut > ../myOut.txt
ls -1ut > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаги сортирующие по времени приведенные в обратном порядке
echo "   14) ls -ltu  (flags -u -t can conflict)"
./ft_ls -1tu > ../myOut.txt
ls -1tu > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаги сортирующие по времени
echo "   15) ls -lutr (flags -u -t can conflict)"
./ft_ls -lutr > ../myOut.txt
ls -lutr > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаги сортирующие по времени приведенные в обратном порядке
echo "   16) ls -ltur (flags -u -t can conflict)"
./ft_ls -ltur > ../myOut.txt
ls -ltur > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаги сортирующие по времени
echo "   17) ls -1utr (flags -u -t can conflict)"
./ft_ls -1utr > ../myOut.txt
ls -1utr > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаги сортирующие по времени приведенные в обратном порядке
echo "   18) ls -ltur (flags -u -t can conflict)"
./ft_ls -1tur > ../myOut.txt
ls -1tur > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаг сортирующий по времени и флаг запрещающий сортировку
echo "   21) ls -ltf  (flags -f -t can conflict)"
./ft_ls -ltf > ../myOut.txt
ls -ltf > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаг сортирующий по времени и флаг запрещающий сортировку
echo "   22) ls -lft  (flags -f -t can conflict)"
ls -lft > ../origOut.txt
./ft_ls -lft > ../myOut.txt
cmp ../myOut.txt ../origOut.txt


## Флаг сортирующий по времени и флаг запрещающий сортировку
echo "   101) ls -lf  (flags -f -l can conflict)"
./ft_ls -lf > ../myOut.txt
ls -lf > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаг сортирующий по времени и флаг запрещающий сортировку
echo "   102) ls -1f  (flags -f -1 can conflict)"
./ft_ls -1f > ../myOut.txt
ls -1f > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаг сортирующий по времени и флаг запрещающий сортировку
echo "   103) ls -f1  (flags -f -1 can conflict)"
./ft_ls -f1 > ../myOut.txt
ls -f1 > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаг сортирующий по времени и флаг запрещающий сортировку
echo "   104) ls -1f  (flags -f -1 can conflict)"
./ft_ls -1f > ../myOut.txt
ls -1f > ../origOut.txt
cmp ../myOut.txt ../origOut.txt

## Флаг сортирующий по времени и флаг запрещающий сортировку
echo "   105) ls -f (in folder should not be to many files)"
./ft_ls -f > ../myOut.txt
ls -f > ../origOut.txt
cmp ../myOut.txt ../origOut.txt
