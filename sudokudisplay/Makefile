# Makefile

CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_ttf SDL2_image`
LDFLAGS =
LDLIBS = -lm `pkg-config --libs sdl2 SDL2_ttf SDL2_image`

all: sudokudisplay

SRC = sudokudisplay.c
OBJ = ${SRC:.c=.o}
EXE = ${SRC:.c=}

sudokudisplay: sudokudisplay.o

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${EXE}

# END
