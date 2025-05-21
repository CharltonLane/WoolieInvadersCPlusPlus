#pragma once
#include <vector>
#include <memory>
#include <SDL3_mixer/SDL_mixer.h>
#include "timer.h"
#include "spaceConversion.h"
#include "player.h"
#include "enemy.h"
#include "levelGrid.h"
#include "appState.h"
#include "uiIconRow.h"

class Game {

public:
	Game() = default;

	Game(const Game& other) = delete;

	Game(SDL_Renderer* renderer)
		: m_renderer{ renderer }
		, m_player{ renderer, &m_level, Vector2Int{4, 4} }
		, m_shopLevelBackground{ renderer, "images/world/shop.png" }
		, m_hudBackground{ renderer, "images/hud/hudBackgroundLarge.png" }
		, m_enemies(6)
		, m_handIcons{ renderer, SDL_FRect{137.0f, SpaceConversion::g_gamePixelHeight - 23, 8,8}, "images/hud/hudIconHand.png" }
		, m_heartIcons{ renderer, SDL_FRect{72.0f, SpaceConversion::g_gamePixelHeight - 23, 8,8}, "images/hud/hudIconHeart.png" }
		, m_enemyIcons{ renderer, SDL_FRect{228.0f, SpaceConversion::g_gamePixelHeight - 22, 8,8}, "images/enemy/enemySouth.png" }
		, m_gameOverSFX{ Mix_LoadWAV("audio/gameOver.wav") }
		, m_clockTickSFX{ Mix_LoadWAV("audio/tick.wav") }
	{
		m_hudBackground.SetScreenPosition({ 0, SpaceConversion::g_gamePixelHeight - m_hudBackground.GetImageSize().y() });
	}

	Game& operator=(const Game& other) = delete;

	// Core.
	void HandleInput(const SDL_Event* event);
	GameState Update(const float dt);
	void Render(SDL_Renderer* renderer) const;

	// Other methods.
	void StartGame();
	void EndGame();
	void SpawnNextWave();
	void Reset();
	void DeleteAllEnemies();

	// Getters/Setters.
	const std::string& GetGameOverReason() { return m_gameOverReason; }
	const int GetGameOverScore() const { return m_gameOverScore; }
	int GetEnemiesAliveCount() const;
	bool AreEnemiesAlive() const;

private:
	SDL_Renderer* m_renderer{};

	// Level.
	LevelGrid m_level{};

	// Entities.
	Player m_player{};
	std::vector<std::unique_ptr<Enemy>> m_enemies;

	// Sprites.
	const Sprite m_shopLevelBackground{};
	Sprite m_hudBackground{};

	// Round timer.
	float m_secondsAddedOnNewRound{ 15.0f };
	float m_roundTimerStartDuration{ 30.0f };
	Timer m_roundTimer{ m_roundTimerStartDuration };

	// Waves.
	int m_waveNumber{ 0 };
	Timer m_newWaveTextTimer{ 3 };

	// Input.
	bool m_escapeKeyPressed{ false };

	// Post-game info.
	std::string m_gameOverReason{};
	int m_gameOverScore{ 0 };

	// Audio.
	Mix_Music* m_ingameMusic{ nullptr };
	Mix_Chunk* m_gameOverSFX{ nullptr };

	Mix_Chunk* m_clockTickSFX{ nullptr };
	bool m_lowOnTime{ false };
	int m_tickChannel{ -1 };

	// UI.
	UIIconRow m_handIcons{};
	UIIconRow m_heartIcons{};
	UIIconRow m_enemyIcons{};
};

