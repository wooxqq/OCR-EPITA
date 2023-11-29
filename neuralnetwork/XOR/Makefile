#Makefile

CC=gcc
CPPGFLAGS= -MMD -lm
CFLAGS= -Wall -Wextra
LDLIBS= -lm

all: XOR

SRC= XOR.c

OBJ= ${SRC:.c=.o}

DEP= ${SRC:.c=.}

Xor:XOR.o

make: ${OBJ}
-include ${DEP}
.PHONY: clean

clean:
	${RM} ${OBJ}
	rm XOR

#End
