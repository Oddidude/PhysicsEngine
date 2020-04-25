#ifndef Environment_h
#define Environment_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "PhysicsBody.h"

class Environment {
	public:
		Environment();
		
		void init(const char* title, int x, int y);

		void handleEvents();
		void update();
		void render();
		void clean();

		float randomFloat();
		bool checkSpawns(PhysicsBody* spawn);

		bool running() const { return isRunning; }

		static SDL_Renderer* renderer;

		static const int width = 800;
		static const int height = 640;
	private:
		std::vector<PhysicsBody*> entities;
		bool isRunning = false;
		SDL_Window *window;
};

#endif
