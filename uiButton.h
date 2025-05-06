#pragma once
#include <SDL3/SDL.h>
#include "sprite.h"
#include "spaceConversion.h"

class UIButton
{
	// This is an onscreen UI button clickable via the mouse.
	// It has a position and size, which is passed to its sprite.
	// It has different visuals for hover and non-hover.
	// It can check if a click is within it's rect.
	// Functionality caused by clicking the button is implemented at the caller, not in this class.

private:
	Sprite m_buttonSprite{};
	SDL_Texture* m_standardTexture{ nullptr };
	SDL_Texture* m_hoverTexture{ nullptr };

	SDL_FRect m_rect{};

public:
	UIButton() = default;

	UIButton(SDL_Renderer* renderer, SDL_FRect rect, const std::string& standardTexturePath, const std::string& hoverTexturePath)
		: m_rect{ rect }
	{
		m_standardTexture = Sprite::LoadImage(renderer, standardTexturePath);
		m_hoverTexture = Sprite::LoadImage(renderer, hoverTexturePath);

		m_buttonSprite.SetRect(m_rect);
		m_buttonSprite.SetTexture(m_standardTexture, false);
	}

	bool IsWithinButton(Vector2& screenPosition) const {
		Vector2 pixelSpacePosition = SpaceConversion::ScreenToPixel(screenPosition);

		return (pixelSpacePosition.x() >= m_rect.x && pixelSpacePosition.x() <= m_rect.x + m_rect.w)
			&& (pixelSpacePosition.y() >= m_rect.y && pixelSpacePosition.y() <= m_rect.y + m_rect.h);
	}

	void Update(Vector2& mousePosition) {
		if (IsWithinButton(mousePosition)) {
			m_buttonSprite.SetTexture(m_hoverTexture, false);
		}
		else {
			m_buttonSprite.SetTexture(m_standardTexture, false);
		}
	}

	void Render(SDL_Renderer* renderer) const {
		m_buttonSprite.Render(renderer);
	}
};

