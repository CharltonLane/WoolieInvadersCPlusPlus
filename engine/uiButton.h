#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "vector2.h"
#include "sprite.h"

class UIButton
{
	// This is an onscreen UI button clickable via the mouse.
	// It has a position and size, which is passed to its sprite.
	// It has different visuals for hover and non-hover.
	// It can check if a click is within it's rect.
	// Functionality caused by clicking the button is implemented at the caller, not in this class.

public:
	UIButton() = default;

	UIButton(SDL_Renderer* renderer, SDL_FRect rect, const std::string& standardTexturePath, const std::string& hoverTexturePath)
		: m_rect{ rect }
		, m_standardTexture{ Sprite::LoadTexture(renderer, standardTexturePath) }
		, m_hoverTexture{ Sprite::LoadTexture(renderer, hoverTexturePath) }
	{
		m_buttonSprite.SetRect(m_rect);
		m_buttonSprite.SetTexture(m_standardTexture, false);

		// We do this here and not in global scope at program start because we need the audio device to be opened by app init.
		if (!m_clickSFX) {
			m_clickSFX = Mix_LoadWAV("audio/buttonClick.wav");
		}
	}

	~UIButton() {
		m_buttonSprite.SetTexture(nullptr, false);
		if (m_standardTexture) {
			SDL_DestroyTexture(m_standardTexture);
		}
		if (m_hoverTexture) {
			SDL_DestroyTexture(m_hoverTexture);
		}
	}

	UIButton(const UIButton& copy) = delete;
	UIButton& operator=(const UIButton& other) = delete;

	bool IsWithinButton(const Vector2& screenPosition, bool click = false) const;

	void Update(const Vector2& mousePosition);

	void Render(SDL_Renderer* renderer) const;


private:
	Sprite m_buttonSprite{};
	SDL_Texture* m_standardTexture{ nullptr };
	SDL_Texture* m_hoverTexture{ nullptr };

	SDL_FRect m_rect{};

	// Audio.
	static Mix_Chunk* m_clickSFX;
};

inline Mix_Chunk* UIButton::m_clickSFX{ nullptr };

