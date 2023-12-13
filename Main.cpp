#include "Game.hpp"
//#include "Joystick.cpp"

Game *game = nullptr;
//Controller *controller = nullptr;


int width = 800;
int height = 600;

//int bpp = 0;

//int flags = 0;


static const GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f
};


int main(int argc, const char * argv[]) 
{	

	game = new Game();

	game->init("Wet Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false);

	while(game->getRunning()) {
		
		game->handleEvents();
		game->update();
		game->render();
	}
	
	game->clean();
	

	return 0;
}
