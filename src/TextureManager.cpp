#ifndef TextureManager_cpp
#define TextureManager_cpp

#include "../headers/TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Environment::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Environment::renderer, tex, &src, &dest);
}
#endif
