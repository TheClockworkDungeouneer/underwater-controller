
#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

class Game {
	public:
		Game();
		~Game();

		void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
		void handleEvents();
		void update();
		void preDraw();
		void render();
		void clean();
		
		bool getRunning() {return isRunning;}
	private:
		int win_width;
		int win_height;

		SDL_GLContext openGLContext;

		//const SDL_RendererInfo* info;

		bool isRunning;
		SDL_Window *window;
		SDL_Renderer *renderer;

};

#endif /* Game_hpp */

