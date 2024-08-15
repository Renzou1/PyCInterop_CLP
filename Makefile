CC = gcc
CFLAGS = -fPIC -shared
SRC = mandelbrot.c
DEST = mandelbrot.so

build:
	$(CC) $(CFLAGS) -o $(DEST) $(SRC)

run:
	python gui.py


