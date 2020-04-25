#ifndef Environment_cpp
#define Environment_cpp

#include "../headers/Environment.h"
#include "../headers/TextureManager.h"
#include "../headers/Circle.h"
#include <math.h>
#include <ctime>

SDL_Renderer* Environment::renderer = nullptr;

Environment::Environment() {}

void Environment::init(const char *title, int x, int y) {
	int flags = 0;
	int noOfCircles = 15;
	int circleX, circleY;

	srand(static_cast<unsigned>(time(0)));

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Initialised..." << std::endl;

		window = SDL_CreateWindow(title, x, y, Environment::width, Environment::height, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}

	/*
	for (int i = 0; i < noOfCircles; i++) {
		do {
			circleX = rand() % (Environment::width - 64);
			circleY = rand() % (Environment::height - 64);
		} while (!checkSpawns(new PhysicsBody(circleX, circleY, 32, 0)));

		entities.push_back(new Circle("../assets/circle.png", circleX, circleY));

		PVector* force = new PVector(randomFloat(), randomFloat());
		entities.back()->applyForce(force);
		delete force;
	}
	*/

	entities.push_back(new Circle("../assets/circle.png", Environment::width / 2, Environment::height / 2));
}

void Environment::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}
}

void Environment::update() {
	for (int i = 0; i < entities.size(); i++) {
		for (int j = i + 1; j < entities.size(); j++) {
			if (entities[i]->checkCollision(entities[j])) {
				entities[i]->bounce(entities[j]);
			}
		}
		entities[i]->update();
	}
}

void Environment::render() {
	SDL_RenderClear(renderer);

	for (auto entity : entities) {
		entity->render();
	}

	SDL_RenderPresent(renderer);
}

void Environment::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	for (auto entity : entities) {
		delete entity;
	}

	std::cout << "Environment cleaned!" << std::endl;
}

float Environment::randomFloat() {
    return ((float(rand()) / float(RAND_MAX)) * 20.0) - 10.0;
}

bool Environment::checkSpawns(PhysicsBody* spawn) {
	for (auto entity : entities) {
		if (spawn->checkCollision(entity)) {
			delete spawn;
			return false;
		}
	}
	delete spawn;
	return true;
}

#endif
