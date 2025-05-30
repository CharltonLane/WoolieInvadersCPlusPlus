#pragma once
#include <vector>
#include <memory>
#include <SDL3/SDL.h>
#include "vector2.h"
#include "sprite.h"

class UIIconRow
{
	// A horizontal group of items to be displayed as UI.
	// These show a quantity visually, rather than drawing a number to the UI which is boring.
public:
	UIIconRow() = default;

	UIIconRow(SDL_Renderer* renderer, const SDL_FRect positionAndSize, const std::string& iconFilePath)
		:m_renderer{ renderer }
		, m_position{ positionAndSize.x, positionAndSize.y }
		, m_spriteSize{positionAndSize.w, positionAndSize.h}
		, m_iconTexture{ Sprite::LoadTexture(renderer, iconFilePath) }
	{}

	~UIIconRow() {

		for (auto& sprite : m_sprites)
		{
			if (sprite) {
				// Clear the texture (we delete it below, instead of letting the sprite delete it).
				sprite->SetTexture(nullptr, false);
			}
			m_sprites.clear();
		}

		SDL_DestroyTexture(m_iconTexture);
	}

	void Render(SDL_Renderer* renderer) const;

	void SetIconsToShow(int count);

private:
	SDL_Renderer* m_renderer{ nullptr };

	Vector2 m_position{}; // In pixel space.
	Vector2 m_spriteSize{};
	SDL_Texture* m_iconTexture{ nullptr };

	std::vector<std::unique_ptr<Sprite>> m_sprites{};

	int m_iconsToShow = 0;

	void AddNewSprite() {
		// Add another sprite to the vector of sprites.
		std::unique_ptr<Sprite> sprite = std::make_unique<Sprite>(m_iconTexture);
		sprite->SetImageSize(m_spriteSize);
		sprite->SetScreenPosition({ m_position.x() + m_spriteSize.x() * (m_sprites.size()), m_position.y() });
		m_sprites.push_back(std::move(sprite));
	}
};

