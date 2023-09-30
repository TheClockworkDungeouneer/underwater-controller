#include<SDL2/SDL.h>
#include<iostream>

#define DEAD_ZONE 3200

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

