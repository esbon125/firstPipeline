BINARY=firstPipeline.out
CC=gcc
CFLAGS=-g -Wall
LDFLAGS= -lm -lGLEW -lGLU -lGL -lglut
SOURCE_BIN=firstPipeline.c

all: $(BINARY)

$(BINARY): $(SOURCE_BIN)
	$(CC) -o $(BINARY) $(CFLAGS) $(LDFLAGS) $(SOURCE_BIN)

clean:
	@rm *.out *.txt