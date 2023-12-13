#ifndef Joystick_hpp
#define Joystick_hpp

#include <SDL2/SDL.h>
#include <iostream>

//#ifndef rectX

//int rectX;
//int rectY;

//#endif

//rectX = 10;
//rectY = 10;

class Vector2D {

	public:
	Vector2D(float _x = 0, float _y = 0)
	{
		x = _x;
		y = _y;
	}

	
	void update(float _x = 0, float _y = 0)
	{
		x = _x;
		y = _y;
	}

	void updateX(float _x = 0)
	{
		x = _x;
	}

	void updateY(float _y = 0)
	{
		y = _y;
	}

	float getX() {return x;}
	float getY() {return y;}

	Vector2D operator+(Vector2D const v1)
	{
		return Vector2D(this->x + v1.x, this->y + v1.y);
	}
	
	Vector2D operator+(const float (&v1)[2])
	{
		return Vector2D(this->x + v1[0], this->y + v1[1]);
	}
	private:

	float x;
	float y;
};

//Vector2D operator+(Vector2D const& v0, Vector2D const& v1)

//Vector2D operator+(Vector2D const& v0, const float (&v1)[2])

class Controller {
	public:
		Controller();
		~Controller();

		void init(int port);
		void init() {init(0);}
		void handleEvents(const SDL_Event *ev);
		void update();
		//void render();
		void clean();
		
		bool getConnected() {return isConnected;}
		
		Vector2D getJoyVector() {return joyVector;}

	private:
		
		bool isConnected;
		SDL_Joystick *joystick;
		SDL_Window *window;
		SDL_Renderer *renderer;
		
		Vector2D joyVector;	
		
};
	


#endif /* Joystick.hpp */
