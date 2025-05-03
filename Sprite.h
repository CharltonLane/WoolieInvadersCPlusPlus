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

public:

	Sprite(SDL_Renderer* renderer, const std::string& fileName) 
		: m_texture{ loadImage(renderer, fileName) }
		, m_rect {}
	{
		m_rect.x = 0; //the x coordinate
		m_rect.y = 0; //the y coordinate

		float width{0};
		float height{ 0 };
		if (SDL_GetTextureSize(m_texture, &width, &height)) {
			m_rect.w = width; //the width of the texture
			m_rect.h = height; //the height of the texture
		}
		else {
			m_rect.w = 16; //the width of the texture
			m_rect.h = 16; //the height of the texture
		}



	}

	Sprite() 
		: m_texture{ nullptr }
		, m_rect{} 
	{}

	SDL_Texture* loadImage(SDL_Renderer* renderer, const std::string& fileName);

	void Render(SDL_Renderer* renderer) const;

	void SetWorldPosition(Vector2 worldPosition);
	void SetScreenPosition(Vector2 position);
};

