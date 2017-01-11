CC=gcc
CFLAGS=-Wall -ansi -g
#CFLAGS=-Wall -std=c99 -g -pg
#CFLAGS=-Wall -std=c99 -O2 -march=native
ODIR=objects/
SRCDIR=src/
INCDIR=include/
OBJ1=$(ODIR)tokenizer.o

all: tokenizer

$(ODIR)%.o: $(SRCDIR)%.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INCDIR)

tokenizer: $(OBJ1)
	$(CC) -o $@ $(CFLAGS) $^ -I$(INCDIR)

