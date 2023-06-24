CC = gcc
CFLAGS = -Wall -g

HEADF = $(wildcard ./Include/*.h)
CONFIG = $(wildcard ./Config/*)
SOURCE = $(wildcard ./Src/*.c)

main: main.c $(SOURCE) $(HEADF) $(CONFIG)
	$(CC) -o $@ $< $(SOURCE) $(CFLAGS) -lm

clean:
	rm -f main
