#ifndef Fluid_cpp
#define Fluid_cpp

#include "../headers/Fluid.h"
#include "../headers/Environment.h"

Fluid::Fluid(float x, float y, int _r, int _g, int _b, int _a)
	: PhysicsBody { x, y, 1 , 1 }, r(_r), g(_g), b(_b), a(_a)
{}

void Fluid::update() {
	if (gravity) {
		accel->add(PhysicsBody::gravityVector);
	}
	vel->add(this->accel);
}

void Fluid::render() {
	SDL_SetRenderDrawColor(Environment::renderer, r, g, b, a);
	SDL_RenderDrawPoint(Environment::renderer, pos->x, pos->y);
	SDL_SetRenderDrawColor(Environment::renderer, 255, 255, 255, 255);
}

#endif
