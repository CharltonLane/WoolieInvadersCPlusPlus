#pragma once
#include "gridEntity.h"
#include "vector2.h"
#include <vector>
#include "timer.h"
#include "spaceConversion.h"
#include "player.h"
#include "enemy.h"

class Game {
private:
	// Entities.
	Player m_player{};
	std::vector<Enemy> m_enemies;

	// Sprites.
	Sprite m_shopBackground{};
	Sprite m_hudBackground{};

	// Round timer.
	float m_roundTimerStartDuration{ 30.0f };
	Timer m_roundTimer{ m_roundTimerStartDuration };

	SDL_Renderer* m_renderer{};

	int m_waveNumber{ 0 };
	bool m_enemiesAlive{ false };

public:
	Game() = default;

	Game(SDL_Renderer* renderer)
		: m_renderer{ renderer }
		, m_player{ renderer, Vector2Int{4, 4}, "images/player/playerDown.png" }
		, m_shopBackground{ renderer, "images/world/shop.png" }
		, m_hudBackground{ renderer, "images/hud/hudBG.png" }
		, m_enemies(6)
	{
		m_hudBackground.SetScreenPosition(Vector2{ 0, SpaceConversion::g_gamePixelHeight - m_hudBackground.GetImageSize().y() });
	}

	void HandleInput(const SDL_Event* event);
	void Update(const float dt);
	void Render(SDL_Renderer* renderer) const;

	bool AreEnemiesAlive() const {
		return m_enemiesAlive;
	}
	void SpawnNextWave();
};

