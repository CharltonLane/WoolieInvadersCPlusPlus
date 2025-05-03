#pragma once
#include <SDL3/SDL.h>
#include "gridEntity.h"
#include "timer.h"

class Player : public GridEntity
{
private:

	// Player health.
	int m_maxHealth{ 5 };
	int m_gameStartHealth{ 3 };

	int m_health{ m_gameStartHealth };

	// Player ammo.
	int m_maxAmmo{ 6 };

	int m_ammo{ m_maxAmmo };
	Timer m_ammoRegenTimer{ 1.5f }; // 1.5 seconds to regen 1 ammo.

	// Player invincibility after being hit.
	Timer m_invincibilityTimer{ 3 }; // 3 seconds of invincibility after taking damage.

	bool m_isNorthInput{ false };
	bool m_isEastInput{ false };
	bool m_isSouthInput{ false };
	bool m_isWestInput{ false };

	// Sprites.
	SDL_Texture* m_northTexture{nullptr};
	SDL_Texture* m_eastTexture{ nullptr };
	SDL_Texture* m_southTexture{ nullptr };
	SDL_Texture* m_westTexture{ nullptr };

public:
	Player() = default;

	Player(SDL_Renderer* renderer, Vector2Int gridPosition)
		: GridEntity{ renderer, gridPosition }
	{
		// Load player textures.
		m_northTexture = Sprite::LoadImage(renderer, "images/player/playerNorth.png");
		m_eastTexture = Sprite::LoadImage(renderer, "images/player/playerEast.png");
		m_southTexture = Sprite::LoadImage(renderer, "images/player/playerSouth.png");
		m_westTexture = Sprite::LoadImage(renderer, "images/player/playerWest.png");

		m_sprite.SetTexture(m_northTexture);
	}

	void CalculateDesiredDirection() override;
	void HandleInput(const SDL_Event* event);
	void Render(SDL_Renderer* renderer) const override;
	void Update(float dt) override;
};

