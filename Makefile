OBJS = Joystick.cpp
MAIN_OBJS = Main.cpp Game.cpp Game.hpp Joystick.cpp Joystick.hpp
CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -ldl -lGL -lGLU -lglut

OBJ_NAME = Joystick.o

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main : Main.cpp
	$(CC) $(MAIN_OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o main.o

depend:
	sudo apt-get update && sudo apt-get install libsdl2-dev

