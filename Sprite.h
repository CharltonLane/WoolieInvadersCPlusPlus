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
		m_rect.w = 50; //the width of the texture
		m_rect.h = 50; //the height of the texture
	}

	Sprite() 
		: m_texture{ nullptr }
		, m_rect{} 
	{}

	SDL_Texture* loadImage(SDL_Renderer* renderer, const std::string& fileName);

	void Render(SDL_Renderer* renderer) const;

	void SetPosition(Vector2 position);
};

