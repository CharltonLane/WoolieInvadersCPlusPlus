#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "vector2.h"

class Sprite
{
	/*
	A Sprite is an image at a position.
	*/
private:
	SDL_Texture* m_texture;
	SDL_FRect m_rect;

	float m_rotationDegrees; // Degrees, clockwise.

public:

	Sprite(SDL_Renderer* renderer, const std::string& fileName)
		: m_texture{ LoadImage(renderer, fileName) }
		, m_rect{}
	{
		m_rect.x = 0; //the x coordinate
		m_rect.y = 0; //the y coordinate

		Vector2 imageSize = GetImageSize();
		m_rect.w = imageSize.x(); //the width of the texture
		m_rect.h = imageSize.y(); //the height of the texture
	}

	Sprite()
		: m_texture{ nullptr }
		, m_rect{}
	{}

	static SDL_Texture* LoadImage(SDL_Renderer* renderer, const std::string& fileName);

	void Render(SDL_Renderer* renderer) const;

	void SetWorldPosition(Vector2 worldPosition);
	void SetScreenPosition(Vector2 position);
	void SetTexture(SDL_Texture* texture);
	void SetImageSize(Vector2 newSize);
	void SetRotation(float degrees);

	float GetRotation() const;
	Vector2 GetImageSize() const;
};

