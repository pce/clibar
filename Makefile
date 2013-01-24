EXE = cli
CC = gcc
CFLAGS = -Wall -g 
#LIBS = `pkg-config --cflags --libs gtk+-2.0` 
LIBS =
FILES = example.c
OBJECTS=


$(EXE): $(OBJECTS)

#example
all: 
	$(CC) $(CFLAGS) $(FILES) -o $(EXE) $(LIBS)

clean:
	rm -f $(EXE) *.o

memcheck:
	valgrind --tool=memcheck ./$(EXE)

fullmemcheck:
	valgrind --leak-check=full --show-reachable=yes --tool=memcheck ./$(EXE)


