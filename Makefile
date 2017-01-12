CC=gcc
CFLAGS=-Wall -ansi -g
#CFLAGS=-Wall -std=c99 -g -pg
#CFLAGS=-Wall -std=c99 -O2 -march=native
ODIR=objects/
SRCDIR=src/
INCDIR=include/
OBJ1=$(ODIR)token.o

all: token

$(ODIR)%.o: $(SRCDIR)%.c
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INCDIR)

token: $(OBJ1)
	$(CC) -o $@ $(CFLAGS) $^ -I$(INCDIR)

test: token
	git pull
	sleep 1
	make
	./token assets/test.cpp

