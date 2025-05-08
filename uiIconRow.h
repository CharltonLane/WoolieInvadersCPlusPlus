#pragma once
#include <vector>
#include <iostream>
#include <SDL3/SDL.h>
#include "vector2.h"
#include "sprite.h"

class UIIconRow
{
	// A horizontal group of items to be displayed as UI.
	// These show a quantity visually, rather than drawing a number to the UI which is boring.
private:
	SDL_Renderer* m_renderer{ nullptr };

	Vector2 m_position{}; // In pixel space.
	Vector2 m_spriteSize{};
	SDL_Texture* m_iconTexture{nullptr};

	std::vector<Sprite*> m_sprites{};

	int m_iconsToShow = 0;

	void AddNewSprite() {
		// Add another sprite to the vector of sprites.
		Sprite* sprite = new Sprite{ m_iconTexture };
		sprite->SetImageSize(m_spriteSize);
		sprite->SetScreenPosition({ m_position.x() + m_spriteSize.x() * (m_sprites.size()), m_position.y() });
		m_sprites.push_back(sprite);
	}

public:
	UIIconRow() = default;

	UIIconRow(SDL_Renderer* renderer, const SDL_FRect positionAndSize, const std::string& iconFilePath)
		:m_renderer{ renderer }
		, m_position{ positionAndSize.x, positionAndSize.y }
		, m_spriteSize{positionAndSize.w, positionAndSize.h}
		, m_iconTexture{ Sprite::LoadImage(renderer, iconFilePath) }
	{}

	void Render(SDL_Renderer* renderer) const {
		if (m_sprites.size() < m_iconsToShow) {
			std::cout << "Not enough icons!\n";
			return;
		}
		auto iconsToShow = static_cast<size_t>(m_iconsToShow);
		for (size_t i = 0; i < iconsToShow; i++)
		{
			m_sprites[i]->Render(renderer);
		}
	}

	void SetIconsToShow(int count) {
		m_iconsToShow = count;
		int currentSpriteCount{ static_cast<int>(m_sprites.size()) };
		if (currentSpriteCount < count) {
			int spritesToAdd{ count - currentSpriteCount };
			for (int i = 0; i < spritesToAdd; i++)
			{
				AddNewSprite();
			}
		}
	}

};

