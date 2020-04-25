#ifndef main_cpp
#define main_cpp

#include "../headers/Environment.h"

Environment *env = nullptr;

int main(int argc, const char* argv[]) {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	env = new Environment();
	env->init("Physics Environment",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED
		  );

	while (env->running()) {
		frameStart = SDL_GetTicks();

		env->handleEvents();
		env->update();
		env->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	env->clean();
	delete env;
	return 0;
}

#endif
