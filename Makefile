EXE = cli
MAIN= example.c
CC = gcc
CFLAGS = -Wall -W -o
#CFLAGS = -Wall -W -Os -g -o
LIBS = 
DEFS=-D_GNU_SOURCE=1
#DEFS= -D_BSD_SOURCE=1
OBJECTS=clibar.o

$(EXE): $(OBJECTS)
	$(MAKE) all

$(OBJECTS): 
	$(CC) -c clibar.c

all: clibar.c example.c
	$(CC) $(DEFS) $(MAIN) $(CFLAGS) $(EXE) $(OBJECTS) $(LIBS)

clean:
	rm -f $(EXE) *.o

memcheck:
	valgrind --tool=memcheck ./$(EXE)

fullmemcheck:
	valgrind --leak-check=full --show-reachable=yes --tool=memcheck ./$(EXE)

