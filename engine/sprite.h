#pragma once

#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "vector2.h"

class Sprite
{
	// A Sprite is an image at a position.

public:

	Sprite()
		: m_texture{ nullptr }
		, m_rect{}
	{}

	Sprite(SDL_Texture* texture)
		: m_texture{ texture }
		, m_rect{}
	{
		m_rect.x = 0; 
		m_rect.y = 0; 

		Vector2 imageSize = GetImageSize();
		m_rect.w = imageSize.x(); 
		m_rect.h = imageSize.y(); 
	}

	Sprite(SDL_Renderer* renderer, const std::string& fileName)
		: Sprite{ LoadTexture(renderer, fileName) }
	{}

	~Sprite() {
		if (m_texture) {
			SDL_DestroyTexture(m_texture);
		}
	}

	// No copying of sprites as SDL_Texture can't be easily copied.
	Sprite(const Sprite& copy) = delete;
	Sprite& operator=(const Sprite& other) = delete;


	void Render(SDL_Renderer* renderer, const Vector2& cameraPosition = {}) const;

	void SetWorldPosition(const Vector2& worldPosition);
	void SetScreenPosition(const Vector2& position);
	void SetTexture(SDL_Texture* texture, bool resizeToTexture = true);
	void SetImageSize(const Vector2& newSize);
	void SetRect(SDL_FRect rect) { m_rect = rect; }
	void SetRotation(float degrees);

	float GetRotation() const;
	Vector2 GetImageSize() const;


	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& fileName);


private:
	SDL_Texture* m_texture;
	SDL_FRect m_rect;

	float m_rotationDegrees{ 0.0f }; // Degrees, clockwise.
};

