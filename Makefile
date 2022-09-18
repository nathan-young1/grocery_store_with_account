# compiler
CC = gcc
CFLAGS = -Wall

# path to all c files include used in program
INCLUDEDIRS = ./lib/*.c

# path to main.c
MAIN = ./src/main.c

# path to store output of compilation
OUTPUT = ./output/main

# command to build the project.
all:
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $(MAIN) -o $(OUTPUT)

clean:
	rm $(OUTPUT)

exec:
	make && $(OUTPUT)