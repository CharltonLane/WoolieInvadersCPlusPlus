#include <SDL3/SDL.h>
#include "game.h"
#include "timer.h"
#include "spaceConversion.h"
#include "random.h"

void Game::HandleInput(const SDL_Event* event)
{
	m_player.HandleInput(event);
}

void Game::Update(const float dt) {
	m_roundTimer.Tick(dt);

	m_player.Update(dt);

	for (auto enemyPointer : m_enemies)
	{
		if (enemyPointer) {
			enemyPointer->Update(dt);
			if (enemyPointer->IsCollidingWith(m_player)) {
				m_player.TakeDamage();
			}
		}
	}

	// See if the player is dead.
	if (!m_player.IsAlive()) {
		std::cout << "GAME OVER!" << "\n";
	}
	// See if the player has run out of time.
	if (m_roundTimer.HasTimerLapsed()) {
		std::cout << "GAME OVER!" << "\n";
	}

	if (!AreEnemiesAlive()) {
		SpawnNextWave();
	}
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
}

void Game::SpawnNextWave()
{
	m_waveNumber++;
	int enemiesToSpawn = 5;

	for (int i = 0; i < enemiesToSpawn; i++)
	{
		int x = Random::get(0, 10);
		int y = Random::get(0, 10);
		m_enemies[i] = new Enemy{ m_renderer, &m_level, Vector2Int{x, y} };
	}
}
