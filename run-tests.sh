

CC=clang
CC=gcc

cd test && $CC TestCliBar.c ../src/clibar.c ../unity/src/unity.c -o testClibar && ./testCliBar



