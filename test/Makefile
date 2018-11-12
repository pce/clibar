# CC = gcc
# ifeq ($(shell uname -s), Darwin)
CC = clang
# endif

CFLAGS=
DEFINES=
INC_DIR=
SRC=TestCliBar.c ../src/clibar.c ../unity/src/unity.c
TARGET=testClibar


test: $(SRC) 
	$(CC) $(CFLAGS) $(DEFINES) $(INC_DIR) $(SRC) -o $(TARGET)
	./$(TARGET)


