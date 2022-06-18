CC := gcc

LIBS := -lpng

CFLAGS := -g -Wall -Wpedantic

all: build/main

build/main: src/main.c
	mkdir -p build/
	${CC} ${CFLAGS} src/main.c -o $@ ${LIBS}

clean:
	rm -rf build/
