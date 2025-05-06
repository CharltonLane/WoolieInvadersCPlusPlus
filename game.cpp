#include <SDL3/SDL.h>
#include "game.h"
#include "timer.h"
#include "spaceConversion.h"
#include "random.h"
#include "appState.h"

void Game::HandleInput(const SDL_Event* event)
{
	if (event->type == SDL_EVENT_KEY_DOWN) {
		if (event->key.repeat) {
			// Ignore repeats caused by holding down the key.
			return;
		}

		if (event->key.key == SDLK_ESCAPE) {
			m_escapeKeyPressed = true;
		}
	}

	m_player.HandleInput(event);
}

GameState Game::Update(const float dt) {
	m_roundTimer.Tick(dt);

	// Update the player and their projectiles.
	m_player.Update(dt);
	m_player.UpdateProjectiles(dt, m_enemies);


	// Update enemies.
	for (auto& enemyPointer : m_enemies)
	{
		if (enemyPointer) {
			enemyPointer->Update(dt);
			if (enemyPointer->IsCollidingWith(m_player)) {
				m_player.TakeDamage();
			}

			// Handle dead enemies.
			if (!enemyPointer->IsAlive()) {
				delete enemyPointer;
				enemyPointer = nullptr;
			}
		}
	}


	// See if the player is dead.
	if (!m_player.IsAlive()) {
		std::cout << "GAME OVER! No health!" << "\n";
		return GameState::DeathScreen;
	}
	// See if the player has run out of time.
	if (m_roundTimer.HasTimerLapsed()) {
		std::cout << "GAME OVER! Out of time!" << "\n";
		return GameState::DeathScreen;
	}

	if (!AreEnemiesAlive()) {
		SpawnNextWave();
	}

	m_newWaveTextTimer.Tick(dt);

	if (m_escapeKeyPressed) {
		m_escapeKeyPressed = false;
		return GameState::MainMenu;
	}
	else {
		return GameState::Ingame;
	}

}

static void DrawCenteredText(SDL_Renderer* renderer, std::string text) {
	float x, y;

	/* Center the message and scale it up */
	x = (SpaceConversion::g_gamePixelWidth / 2 - (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(text.c_str()) / 2));
	y = (SpaceConversion::g_gamePixelHeight / 2 - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE / 2);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 127);
	SDL_RenderDebugText(renderer, x + 1, y + 1, text.c_str());

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDebugText(renderer, x, y, text.c_str());

}

void Game::Render(SDL_Renderer* renderer) const {
	// Draw the shop.
	m_shopBackground.Render(renderer);

	// Render entities.
	m_player.Render(renderer);

	for (auto enemyPointer : m_enemies)
	{
		if (enemyPointer) {
			enemyPointer->Render(renderer);
		}
	}

	// Render HUD.
	m_hudBackground.Render(renderer);
	SDL_RenderDebugText(renderer, 118, ((SpaceConversion::g_gamePixelHeight)-SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), std::to_string(static_cast<int>(m_roundTimer.GetTimeRemaining())).c_str());

	if (!m_newWaveTextTimer.HasTimerLapsed()) {
		DrawCenteredText(renderer, "Wave " + std::to_string(m_waveNumber));
	}

}



void Game::SpawnNextWave()
{
	m_waveNumber++;
	int enemiesToSpawn = 2;

	for (int i = 0; i < enemiesToSpawn; i++)
	{
		int x = Random::get(0, 10);
		int y = Random::get(0, 10);
		m_enemies[i] = new Enemy{ m_renderer, &m_level, Vector2Int{x, y} };
	}

	m_newWaveTextTimer.Restart();
}
