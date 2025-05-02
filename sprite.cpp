#include <SDL3/SDL.h>
#include "sprite.h"
#include "vector2.h"

SDL_Texture* Sprite::loadImage(SDL_Renderer* renderer, const std::string& fileName) {
	SDL_Texture* tex = IMG_LoadTexture(renderer, fileName.c_str());
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
	return tex;
}

void Sprite::Render(SDL_Renderer* renderer) const {
	SDL_RenderTexture(renderer, m_texture, NULL, &m_rect);
}

void Sprite::SetPosition(Vector2 position)
{
	m_rect.x = position.x();
	m_rect.y = position.y();
}
