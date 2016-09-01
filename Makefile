SHELL := /bin/bash
CC = gcc
EXEC = commentCleanup
CCFLAGS = --ansi -g -W
OBJS = commentCleanup.o

${EXEC}: ${OBJS}
	${CC} ${CCFLAGS} -o ${EXEC} ${OBJS}

run: ${EXEC} 
	./${EXEC} test.c

.c.o:
	${CC} ${CCFLAGS} -c $<