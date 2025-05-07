#pragma once
#include <SDL3_mixer/SDL_mixer.h>
#include "gridEntity.h"
#include "vector2.h"
#include <vector>
#include "timer.h"
#include "spaceConversion.h"
#include "player.h"
#include "enemy.h"
#include "levelGrid.h"
#include "appState.h"

class Game {
private:
	// Level.
	LevelGrid m_level{};

	// Entities.
	Player m_player{};
	std::vector<Enemy*> m_enemies;

	// Sprites.
	const Sprite m_shopLevelBackground{};
	Sprite m_hudBackground{};

	// Round timer.
	float m_roundTimerStartDuration{ 30.0f };
	Timer m_roundTimer{ m_roundTimerStartDuration };

	SDL_Renderer* m_renderer{};

	int m_waveNumber{ 0 };
	Timer m_newWaveTextTimer{ 3 };

	bool m_escapeKeyPressed{ false };

	std::string m_gameOverReason{};
	int m_gameOverScore{ 0 };

	// Audio.
	Mix_Music* m_ingameMusic;

public:
	Game() = default;

	Game(SDL_Renderer* renderer)
		: m_renderer{ renderer }
		, m_player{ renderer, &m_level, Vector2Int{4, 4}}
		, m_shopLevelBackground{ renderer, "images/world/shop.png" }
		, m_hudBackground{ renderer, "images/hud/hudBG.png" }
		, m_enemies(6, nullptr)
	{
		m_hudBackground.SetScreenPosition(Vector2{ 0, SpaceConversion::g_gamePixelHeight - m_hudBackground.GetImageSize().y() });
	}

	void StartGame() {

		Mix_VolumeMusic(MIX_MAX_VOLUME/2);
		m_ingameMusic = Mix_LoadMUS("audio\\downdown.ogg");
		if (m_ingameMusic) {
			Mix_PlayMusic(m_ingameMusic, -1);
		}
		else {
			printf("Music is null %s\n", SDL_GetError());
		}
	}

	void EndGame() {
		// Fade music over 3 seconds.
		Mix_FadeOutMusic(3000);
	}

	void HandleInput(const SDL_Event* event);
	GameState Update(const float dt);
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
	void Reset() {

		m_gameOverScore = m_player.GetScore();

		m_escapeKeyPressed = false;
		m_roundTimer.SetTimer(m_roundTimerStartDuration);
		m_waveNumber = 0;

		m_player.Reset();
		for (auto& enemy : m_enemies)
		{
			if (enemy) {
				delete enemy;
				enemy = nullptr;
			}
		}
	}

	const std::string& GetGameOverReason() { return m_gameOverReason; }
};

