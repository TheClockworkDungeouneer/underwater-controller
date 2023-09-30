OBJS = joystick.cpp
CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2

OBJ_NAME = joystick.o

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

depend:
	sudo apt-get update && sudo apt-get install libsdl2-dev

