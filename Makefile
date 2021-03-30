CC=gcc
CFLAGS=-g -Wall
OBJS=main.o key.o permutate.o common.o round.o
TARGET=DES

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
	
main.o: common.h round.h key.h permutate.h main.c
common.o: common.h common.c
permutate.o: common.h permutate.h permutate.c
round.o: common.h round.h permutate.h round.c
key.o: common.h key.h key.c