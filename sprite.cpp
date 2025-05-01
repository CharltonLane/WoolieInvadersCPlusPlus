#include "Sprite.h"

SDL_Texture* Sprite::loadImage(SDL_Renderer* renderer, std::string& fileName) {
	SDL_Texture* tex = IMG_LoadTexture(renderer, fileName.c_str());
	return tex;
}

void Sprite::Render(SDL_Renderer* renderer) const {
	SDL_RenderTexture(renderer, m_texture, NULL, &m_rect);
}