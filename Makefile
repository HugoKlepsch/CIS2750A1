CC=gcc
CFLAGS=-Wall -std=c99 -g
#CFLAGS=-Wall -std=c99 -g -pg
#CFLAGS=-Wall -std=c99 -O2 -march=native
ODIR=objects/
SRCDIR=src/
INCDIR=include/
OBJ1=$(ODIR)shell.o

all: shell

$(ODIR)%.o: $(SRCDIR)%.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INCDIR)

avltree: $(OBJ1)
	$(CC) -o $@ $(CFLAGS) $^ -I$(INCDIR)

