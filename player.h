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

public:
	Player() = default;

	Player(SDL_Renderer* renderer, Vector2Int gridPosition, const std::string& spriteFilePath)
		: GridEntity{ renderer, gridPosition, spriteFilePath }
	{}

	void CalculateDesiredDirection() override;
	void HandleInput(const SDL_Event* event);
};

