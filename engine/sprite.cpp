#include <cassert>
#include <iostream>
#include <SDL3/SDL.h>
#include "sprite.h"
#include "vector2.h"
#include "spaceConversion.h"

SDL_Texture* Sprite::LoadTexture(SDL_Renderer* renderer, const std::string& fileName) {
	SDL_Texture* tex = IMG_LoadTexture(renderer, fileName.c_str());
	SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);

	assert((tex != NULL && ("Failed to load texture from filename " + fileName).c_str()));

	return tex;
}

void Sprite::Render(SDL_Renderer* renderer, const Vector2& cameraPosition) const {

	SDL_FRect cameraOffsetPosition
	{   m_rect.x - cameraPosition.x(),
		m_rect.y - cameraPosition.y(),
		m_rect.w, 
		m_rect.h 
	};

	if (m_rotationDegrees == 0) {
		SDL_RenderTexture(renderer, m_texture, NULL, &cameraOffsetPosition);
	}
	else {
		SDL_FPoint center{};
		center.x = m_rect.w / 2;
		center.y = m_rect.h / 2;
		SDL_RenderTextureRotated(renderer, m_texture, NULL, &cameraOffsetPosition, m_rotationDegrees, &center, SDL_FLIP_NONE);
	}

}

void Sprite::SetWorldPosition(const Vector2& worldPosition)
{
	Vector2 screenPosition = SpaceConversion::WorldToPixel(worldPosition);
	m_rect.x = screenPosition.x();
	m_rect.y = screenPosition.y();
}

void Sprite::SetScreenPosition(const Vector2& position)
{
	m_rect.x = position.x();
	m_rect.y = position.y();
}

void Sprite::SetTexture(SDL_Texture* texture, bool resizeToTexture) {
	if (m_texture == texture) {
		return;
	}
	m_texture = texture;

	if (resizeToTexture) {
		Vector2 imageSize = GetImageSize();
		m_rect.w = imageSize.x(); //the width of the texture
		m_rect.h = imageSize.y(); //the height of the texture
	}
}

void Sprite::SetImageSize(const Vector2& newSize) {
	//std::cout << "Set size of sprite to " << newSize << "\n";
	m_rect.w = newSize.x(); //the width of the texture
	m_rect.h = newSize.y(); //the height of the texture
}


void Sprite::SetRotation(const float degrees) {
	m_rotationDegrees = fmodf(degrees, 360.0f);
	if (m_rotationDegrees < 0) {
		m_rotationDegrees += 360;
	}
}

float Sprite::GetRotation() const {
	return m_rotationDegrees;
}

Vector2 Sprite::GetImageSize() const {
	float width{ 0 };
	float height{ 0 };
	if (m_texture) {
		SDL_GetTextureSize(m_texture, &width, &height);
	}
	return Vector2{ width, height };
}
