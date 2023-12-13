#include "Game.hpp"
#include "Joystick.hpp"
#include <map>



Game::Game()
{}
Game::~Game()
{}

Controller *controller = nullptr;	

//int win_width = 800;
//int win_height = 600;

int rectX;
int rectY;

//const SDL_VideoInfo* info = NULL;
const SDL_RendererInfo* info = NULL;

short unsigned int drawValue = 0;
std::map<unsigned int, unsigned short int> drawSet;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	//bpp = info->vfmt->BitsPerPixel;

	win_width = width;
	win_height = height;

	flags = SDL_WINDOW_OPENGL;

	if(fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "Intitalization Failed: " << SDL_GetError()<< std::endl;
		isRunning = false;
	}

		std::cout << "Subsystems initialized..." << std::endl;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		
		if(window)
		{
			std::cout << "Window Created..." << std::endl;
		}


		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer)
		{
			//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer Created..." << std::endl;
		}
	

		// INIT OpenGL: //


		openGLContext = SDL_GL_CreateContext(window);
		if(!openGLContext)
		{
			//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "OpenGL init failed!" << std::endl;
		}

		//flags = SDL_OPENGL | SDL_FULLSCREEN;

		//if(SDL_SetVideoMode(width, height, bpp, flags) == 0)
		//{
		//	std::cerr << "Video mode set failed: " << SDL_GetError() << std::endl;
		//}


		controller = new Controller();

		controller->init(0);

		std::cout << "Controller Initialized..." << std::endl;
		

		isRunning = true;

}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_JOYAXISMOTION: case SDL_JOYBUTTONDOWN:
			controller->handleEvents(&event);
			break;
		default:
			//std::cerr << "Warning: Unhandled Event..." << std::endl;
			break;
	}
}

void Game::update()
{
	if (rectX < win_width && rectY < win_height && rectX >= 0 && rectY >= 0 && drawValue>10) 
	{
		unsigned int cordHex = (rectY << 16) | rectX;	
		//std::cout << "Value: " << drawValue << "  |  " << (drawValue * (255.0/(2^15-1))) << std::endl;
		drawSet[cordHex] = drawValue;
	}

	/*
	if (rectX < 800 && rectY < 600) 
	{
		int cordHex = (rectX << 2) | rectY;
		drawSet[cordHex] = drawValue;
	}
	*/
}

void Game::preDraw()
{

}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer,0,0,0,255);	
	SDL_RenderClear(renderer);
	//this is where add stuff to render
	
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	SDL_RenderDrawPoint(renderer,100,100);

	for (const auto& [key, value]: drawSet)
	{
		int pValue = value;
		SDL_SetRenderDrawColor(renderer, (int)(value), (int)(value), (int)(value), 255);
		//std::cout << "Cords: " << std::hex << key << std::endl;
		SDL_RenderDrawPoint(renderer, (int) (key & 0x0000FFFF), (int)((key & 0xFFFF0000) >> 16));

	
	}
	
	SDL_SetRenderDrawColor(renderer,255,255,255,255);

	SDL_Rect rect;
	rect.w = 100;
	rect.h = 100;
	rect.x = rectX;
	rect.y = rectY;

	SDL_RenderDrawRect(renderer, &rect);

	//end section
	SDL_RenderPresent(renderer);
	SDL_GL_SwapWindow(window);
}

void Game::clean()
{

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Program Cleanup Complete!" << std::endl;
}

