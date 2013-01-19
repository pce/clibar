EXE = cli
CC = gcc
CFLAGS = -Wall -g 
#LIBS = `pkg-config --cflags --libs gtk+-2.0` 
LIBS =
FILES = cli.c
OBJECTS=


$(EXE): $(OBJECTS)

all: 
	$(MAKE) $(FILES) -o $(EXE) $(LIBS)

clean:
	rm -f $(EXE) *.o


