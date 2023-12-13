#ifndef Joystick_cpp
#define Joystick_cpp
//#include <opencv2/core/affine.hpp>


#include<SDL2/SDL.h>
#include<iostream>
#include<map>
#include<math.h>

#include "Joystick.hpp"

#define DEAD_ZONE 3200

#define ROT_SCALE (1.0/2000)


extern int rectX;
extern int rectY;

extern unsigned short int drawValue;
extern std::map<unsigned int, unsigned short int> drawSet;

Controller::Controller()
{}
Controller::~Controller()
{}


void Controller::init(int port)
{
	joystick = SDL_JoystickOpen(port);

		
	std::cout << "Controller Name: " << SDL_JoystickName(joystick) << std::endl;
	std::cout << "Num Axes: " << SDL_JoystickNumAxes << std::endl;
	std::cout << "Num Buttons: " << SDL_JoystickNumButtons(joystick) << std::endl;

	if(SDL_NumJoysticks() < 1)
		SDL_Log("ERROR: No controllers are attached!");	 


	isConnected = true;

	Controller.joyVector = new Vector2D();	

	std::cout << "PROGRAM STARTED! " << std::endl;
}


void Controller::handleEvents(const SDL_Event *ev)
{
	
//while(isRunning)
//{
	//while(SDL_PollEvent(&ev) != 0)
	//{
		// Getting the quit and the keyboard events
		switch(ev->type)
		{
			//case SDL_QUIT:
			//	isRunning = false;
			//	break;
			case SDL_JOYAXISMOTION:
			switch(ev->jaxis.axis)
			{
				case 0:
					if (ev->jaxis.value < -DEAD_ZONE)
					{
						std::cout << "LEFT MOTION: " << ev->jaxis.value << std::endl;	
						rectX += (ev->jaxis.value + DEAD_ZONE/10 *0) * ROT_SCALE;
					}
					else if (ev->jaxis.value > DEAD_ZONE)
					{
						std::cout << "RIGHT MOTION: " << ev->jaxis.value << std::endl;		
						rectX += (ev->jaxis.value - DEAD_ZONE/10 *0) * ROT_SCALE;
					}
					else
					{
						Controller.joyVector.updateX()
					}
					break;

				case 1:
					if (ev->jaxis.value < -DEAD_ZONE)
					{
						std::cout << "UP MOTION: " << ev->jaxis.value << std::endl;		
						rectY += (ev->jaxis.value + DEAD_ZONE/10 *0) * ROT_SCALE;
					}
					else if (ev->jaxis.value > DEAD_ZONE)
					{
						std::cout << "DOWN MOTION: " << (ev->jaxis.value) << std::endl;	
						rectY += (ev->jaxis.value - DEAD_ZONE/10 *0) * ROT_SCALE;	
					}
					break;
					case 2: case 5:
						if (ev->jaxis.value > DEAD_ZONE)
						{
							drawValue = (ev->jaxis.value * (255.0/(0x8000-1)));
							std::cout << "TRIGGER MOTION (" << (ev->jaxis.value == 2 ? "LEFT" : "RIGHT") << "  |  " << (drawValue) << "): " << (ev->jaxis.value) << std::endl;	


						}
						else {drawValue = 0;}
					break;

					default:
						if (ev->jaxis.value > DEAD_ZONE) {
							std::cout << "MYSTERY MOTION: " << (int) ev->jaxis.axis << " | " << ev->jaxis.value << (ev->jaxis.axis) << std::endl;	
							//printf("Axis: %d", ev->jaxis.axis);
						}
						break;

			}
			break;	

		case SDL_JOYBUTTONDOWN:
			enum button {A,B,X,Y};
			//printf("BUTTON: %d\n", ev.jbutton.button);	

			switch((button) ev->jbutton.button){
				case Y:
					std::cout << "Y BUTTON (yellow)" << std::endl;
					break;	
				case B:
					std::cout << "B BUTTON (red)" << std::endl;	
					break;	
				case A:
					std::cout << "A BUTTON (green)" << std::endl;	
					rectX = rectY = 0;
					break;	
				case X:	
					std::cout << "X BUTTON (blue)" << std::endl;	
					break;	
		      	}
			break;	
		}


	//	}
	//}
}



/*

int main(int argc, char *arg[])
{



if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
{
	fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());	
}

//SDL_JoystickEventState(SDL_ENABLE);
SDL_Joystick *joystick = SDL_JoystickOpen(0);

std::cout << "Controller Name: " << SDL_JoystickName(joystick) << std::endl;
std::cout << "Num Axes: " << SDL_JoystickNumAxes << std::endl;
std::cout << "Num Buttons: " << SDL_JoystickNumButtons(joystick) << std::endl;

if(SDL_NumJoysticks() < 1)
	SDL_Log("ERROR: No controllers are attached!");	 


bool isRunning = true;
SDL_Event ev;

std::cout << "PROGRAM STARTED! " << std::endl;

while(isRunning)
{
	while(SDL_PollEvent(&ev) != 0)
	{
		// Getting the quit and the keyboard events
		switch(ev.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_JOYAXISMOTION:
			if ((ev.jaxis.value < -DEAD_ZONE) && (ev.jaxis.axis == 0))
			{
				std::cout << "LEFT MOTION: " << ev.jaxis.value << std::endl;	
			}
			else if ((ev.jaxis.value > DEAD_ZONE) && (ev.jaxis.axis == 0))
			{
				std::cout << "RIGHT MOTION: " << ev.jaxis.value << std::endl;	
			
			}
			else if ((ev.jaxis.value < -DEAD_ZONE) && (ev.jaxis.axis == 1))
			{
				std::cout << "UP MOTION: " << ev.jaxis.value << std::endl;	
			
			}
			else if ((ev.jaxis.value > DEAD_ZONE) && (ev.jaxis.axis == 1))
			{
				std::cout << "DOWN MOTION: " << ev.jaxis.value << std::endl;	
			
			}
			break;	

		case SDL_JOYBUTTONDOWN:
			enum button {A,B,X,Y};
			//printf("BUTTON: %d\n", ev.jbutton.button);	

			switch((button) ev.jbutton.button){
				case Y:
					std::cout << "Y BUTTON (yellow)" << std::endl;
					break;	
				case B:
					std::cout << "B BUTTON (red)" << std::endl;	
					break;	
				case A:
					std::cout << "A BUTTON (green)" << std::endl;	
					break;	
				case X:	
					std::cout << "X BUTTON (blue)" << std::endl;	
					break;	
		      	}
			break;	

		}

		}
	}
}
*/

/*
				//SDL_Joystick *joyboy;
				switch(ev.jaxis.which)
				{
					case 0:
						printf()

					case 1:

				}

		}
		
		if(ev.type == SDL_QUIT)
			isRunning = false;
		else if(ev.type == SDL_JOYAXISMOTION)
		{
			if(ev.jaxis.which == 0)
			{	
				if(ev.jaxis.axis == 0)
				{
					if(ev.jaxis.value < -DEAD_ZONE)
					{
						std::cout << "LEFT MOTION: " << ev.jaxis.value << std::endl;
					}
					else if(ev.jaxis.value > DEAD_ZONE)
						std::cout << "RIGHT MOTION: " << ev.jaxis.value << std::endl;

				}
			}
*/



#endif
