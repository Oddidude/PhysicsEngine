#ifndef Circle_cpp
#define Circle_cpp

#include "../headers/Circle.h"
#include "../headers/TextureManager.h"
#include <math.h>

Circle::Circle(const char* textureSheet, float x, float y) 
	: PhysicsBody { x, y, 32, 1, true, false }
{
	texture = TextureManager::LoadTexture(textureSheet);

	srcRect.x = srcRect.y = 0;
	srcRect.w = srcRect.h = radius * 2;

	destRect.x = x;
	destRect.y = y;
	destRect.w = destRect.h = radius * 2;
}

void Circle::update() {
	applyAcceleration();
	destRect.x = pos->x;
	destRect.y = pos->y;
}

void Circle::render() {
	TextureManager::Draw(texture, srcRect, destRect);
}

#endif
