#Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 -w `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image`

all: images
SRC= images.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.}
images:images.o
make: ${OBJ}
-include ${DEP}
.PHONY: clean

clean:
	${RM} ${OBJ}
	rm images

#End
