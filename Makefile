OBJS = joystick.cpp
CC = g++
.PHONY: SDL2

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2

OBJ_NAME = joystick.o

$(OBJS) : SDL2

SDL2:
	[ -z `dpkg -l | grep libsdl2-dev` ] && sudo apt-get install libsdl2-dev

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
