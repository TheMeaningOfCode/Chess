#Basic Makefile

OBJS = src/*.cpp src/*.h

CC = g++

COMPILER_FLAGS = -Wall -pedantic -g

LINKER_FLAGS = -lSDL2 -lSDL2_image

OUTPUT = executable

all: compile

compile: $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(OBJS) $(LINKER_FLAGS) -o $(OUTPUT)

run:
	./$(OUTPUT)

clean:
	rm -rf obj/*.o $(OUTPUT)
