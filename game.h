#pragma once
#include "gridEntity.h"
#include "vector2.h"
#include <vector>
#include "timer.h"
#include "spaceConversion.h"
#include "player.h"
#include "enemy.h"
#include "levelGrid.h"

class Game {
private:
	// Level.
	LevelGrid m_level{};

	// Entities.
	Player m_player{};
	std::vector<Enemy*> m_enemies;

	// Sprites.
	Sprite m_shopBackground{};
	Sprite m_hudBackground{};

	// Round timer.
	float m_roundTimerStartDuration{ 30.0f };
	Timer m_roundTimer{ m_roundTimerStartDuration };

	SDL_Renderer* m_renderer{};

	int m_waveNumber{ 0 };
	Timer m_newWaveTextTimer{ 3 };

public:
	Game() = default;

	Game(SDL_Renderer* renderer)
		: m_renderer{ renderer }
		, m_player{ renderer, &m_level, Vector2Int{4, 4}}
		, m_shopBackground{ renderer, "images/world/shop.png" }
		, m_hudBackground{ renderer, "images/hud/hudBG.png" }
		, m_enemies(6, nullptr)
	{
		m_hudBackground.SetScreenPosition(Vector2{ 0, SpaceConversion::g_gamePixelHeight - m_hudBackground.GetImageSize().y() });
	}

	void HandleInput(const SDL_Event* event);
	void Update(const float dt);
	void Render(SDL_Renderer* renderer) const;

	bool AreEnemiesAlive() const {
		for (auto enemyPointer : m_enemies) {
			if (enemyPointer) {
				return true;
			}
		}

		return false;
	}
	void SpawnNextWave();
};

