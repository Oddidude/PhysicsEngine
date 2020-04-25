#ifndef Circle_cpp
#define Circle_cpp

#include "../headers/Circle.h"
#include "../headers/TextureManager.h"
#include <math.h>

Circle::Circle(const char* textureSheet, float x, float y) 
	: PhysicsBody { x, y, 32, 1, true}
{
	texture = TextureManager::LoadTexture(textureSheet);

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = 64;

	destRect.x = x;
	destRect.y = y;
	destRect.w = destRect.h = 64;
	/*
	if (gravity) {
		std::cout << "Gravity: " << gravity << std::endl;
	} else {
		std::cout << "No gravity" << std::endl;
	}
	*/
}

void Circle::update() {
	applyAcceleration();
	destRect.x = getPos()->x;
	destRect.y = getPos()->y;
}

void Circle::render() {
	TextureManager::Draw(texture, srcRect, destRect);
}

#endif
