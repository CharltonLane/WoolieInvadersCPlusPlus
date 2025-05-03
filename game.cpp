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

	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].Update(dt);
	}

	if (!m_enemiesAlive) {
		SpawnNextWave();
	}
}

void Game::Render(SDL_Renderer* renderer) const {
	// Draw the shop.
	m_shopBackground.Render(renderer);

	// Render entities.
	m_player.Render(renderer);

	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].Render(renderer);
	}

	// Render HUD.
	m_hudBackground.Render(renderer);
	SDL_RenderDebugText(renderer, 118, ((SpaceConversion::g_gamePixelHeight)-SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), std::to_string(static_cast<int>(m_roundTimer.GetTimeRemaining())).c_str());
}

void Game::SpawnNextWave()
{
	m_waveNumber++;
	int enemiesToSpawn = 2;

	for (int i = 0; i < enemiesToSpawn; i++)
	{
		int x = Random::get(0, 10);
		int y = Random::get(0, 10);
		m_enemies[i] = Enemy{ m_renderer, Vector2Int{x, y}, "images/enemy/enemyDown.png" };
	}

	m_enemiesAlive = true;

}
