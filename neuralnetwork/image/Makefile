#Makefile

CC=gcc
CPPGFLAGS= -MMD -lm
CFLAGS= -Wall -Wextra
LDLIBS= -lm
all: images
SRC= images.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.}
image:image.o
make: ${OBJ}
-include ${DEP}
.PHONY: clean

clean:
	${RM} ${OBJ}
	rm images

#End
