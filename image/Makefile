# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 -w `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_image`

all: display grayscale rotation binarization

SRC = display.c grayscale.c rotation.c binarization.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

display: display.o
grayscale: grayscale.o
image_rotation: rotation.o
binarization: binarization.o

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END
