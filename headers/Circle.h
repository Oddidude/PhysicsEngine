#ifndef Circle_h
#define Circle_h

#include <SDL2/SDL.h>
#include "PhysicsBody.h"

class Circle : public PhysicsBody {
	public:
		Circle(const char* textureSheet, float x, float y);

		void update();
		void render();

	private:
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;
};

#endif
