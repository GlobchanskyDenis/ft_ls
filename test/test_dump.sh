#!/bin/bash

export LC_ALL=C

# test/origins

## Флаги сортирующие по времени
ls      -ftl  1> ../origOut.txt  2> ../origErrOut.txt
./ft_ls -ftl  1> ../myOut.txt    2> ../myErrOut.txt
cmp ../myOut.txt    ../origOut.txt
cmp ../myErrOut.txt ../origErrOut.txt

# head -n 35 ../myOut.txt ; echo "" ; head -n 35 ../origOut.txt
# head -n 15 ../myErrOut.txt ; echo "" ; head -n 15 ../origErrOut.txt
cat -n ../myOut.txt ; echo "" ; cat -n ../origOut.txt
