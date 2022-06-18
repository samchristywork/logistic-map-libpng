CC := gcc

LIBS := -lpng

CFLAGS := -g -Wall -Wpedantic

all: build/generate_logistic_map

build/generate_logistic_map: src/generate_logistic_map.c
	mkdir -p build/
	${CC} ${CFLAGS} src/generate_logistic_map.c -o $@ ${LIBS}

clean:
	rm -rf build/
