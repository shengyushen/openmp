EXECS = hello.exe for.exe critical.exe
CC=gcc

.DEFAULT_GOAL := all

all: ${EXECS}

%.exe : %.c
	${CC} -fopenmp -o $@ $<

.PHONY: clean

clean:
	rm -f ${EXECS}
