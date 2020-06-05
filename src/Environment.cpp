#ifndef Environment_cpp
#define Environment_cpp

#include "../headers/Environment.h"
#include "../headers/TextureManager.h"
#include "../headers/Circle.h"
#include <math.h>
#include <ctime>

SDL_Renderer* Environment::renderer = nullptr;
SDL_Event event;

Environment::Environment() {}

int count = 0;

void Environment::init(const char *title, int x, int y) {
	int flags = 0;

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
}

void Environment::handleEvents() {
	while (SDL_PollEvent(&event)) {
		std::cout << count++ << std::endl;
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);
					entities.push_back(
							new Circle(
								"../assets/circle.png",
							mouseX - 32,
							mouseY - 32
							)
					);
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						for (auto entity : entities) {
							entity->applyForce(new PVector(randomFloat(), randomFloat()));
						}
						break;
					case SDLK_0:
						for (auto entity : entities) {
							entity->setFrictionLevel(0);
						}
						break;
					case SDLK_1:
						for (auto entity : entities) {
							entity->setFrictionLevel(1);
						}
						break;
					case SDLK_2:
						for (auto entity : entities) {
							entity->setFrictionLevel(2);
						}
						break;
					case SDLK_3:
					case SDLK_4:
					case SDLK_5:
					case SDLK_6:
					case SDLK_7:
					case SDLK_8:
					case SDLK_9:
						for (auto entity : entities) {
							entity->setFrictionLevel(3);
						}
						break;
					case SDLK_g:
						for (auto entity : entities) {
							entity->toggleGravity();
						}
						break;
					case SDLK_q:
						isRunning = false;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void Environment::update() {
	for (int i = 0; i < entities.size(); i++) {
		for (int j = i + 1; j < entities.size(); j++) {
			if (entities[i]->checkCollision(entities[j])) {
				entities[i]->bounce(entities[j]);
				entities[i]->unstuck(entities[j]);
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
	float maxSpeed = entities.back()->getMaxSpeed();
	return ((float(rand()) / float(RAND_MAX)) * (2 * maxSpeed)) - maxSpeed;
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
