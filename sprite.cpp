#include <SDL3/SDL.h>
#include <iostream>
#include "sprite.h"
#include "vector2.h"
#include "spaceConversion.h"
#include <cassert>

SDL_Texture* Sprite::LoadImage(SDL_Renderer* renderer, const std::string& fileName) {
	SDL_Texture* tex = IMG_LoadTexture(renderer, fileName.c_str());
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);

	assert((tex != NULL && ("Failed to load texture from filename " + fileName).c_str()));

	return tex;
}

void Sprite::Render(SDL_Renderer* renderer) const {
	SDL_RenderTexture(renderer, m_texture, NULL, &m_rect);
}

void Sprite::SetWorldPosition(Vector2 worldPosition)
{
	Vector2 screenPosition = SpaceConversion::WorldToPixel(worldPosition);
	//std::cout << screenPosition.x() << ", " << screenPosition.y() << "\n";
	m_rect.x = screenPosition.x();
	m_rect.y = screenPosition.y();
}

void Sprite::SetScreenPosition(Vector2 position)
{
	m_rect.x = position.x();
	m_rect.y = position.y();
}

void Sprite::SetTexture(SDL_Texture* texture) {
	//std::cout << "Set sprite texture" << "\n";
	m_texture = texture;

	Vector2 imageSize = GetImageSize();
	m_rect.w = imageSize.x(); //the width of the texture
	m_rect.h = imageSize.y(); //the height of the texture
}

Vector2 Sprite::GetImageSize() const {
	float width{ 0 };
	float height{ 0 };
	SDL_GetTextureSize(m_texture, &width, &height);
	return Vector2{ width, height };
}
