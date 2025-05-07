#include <SDL3/SDL.h>
#include "game.h"
#include "timer.h"
#include "spaceConversion.h"
#include "random.h"
#include "appState.h"
#include "textRendering.h"

void Game::StartGame() {

	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	m_ingameMusic = Mix_LoadMUS("audio\\downdown.mp3");
	if (m_ingameMusic) {
		Mix_PlayMusic(m_ingameMusic, -1);
	}
	else {
		printf("Music is null %s\n", SDL_GetError());
	}
}

void Game::EndGame() {
	// Fade music over 3 seconds.
	Mix_FadeOutMusic(3000);
}

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
		m_gameOverReason = "You died!";
		Reset();
		return GameState::DeathScreen;
	}
	// See if the player has run out of time.
	if (m_roundTimer.HasTimerLapsed()) {
		std::cout << "GAME OVER! Out of time!" << "\n";
		m_gameOverReason = "Out of time!";
		Reset();
		return GameState::DeathScreen;
	}

	if (!AreEnemiesAlive()) {
		SpawnNextWave();
	}

	m_newWaveTextTimer.Tick(dt);

	if (m_escapeKeyPressed) {
		m_escapeKeyPressed = false;
		Reset();
		return GameState::MainMenu;
	}
	else {
		return GameState::Ingame;
	}

}


void Game::Render(SDL_Renderer* renderer) const {
	// Draw the shop.
	m_shopLevelBackground.Render(renderer);

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

	float bottomRowY = ((SpaceConversion::g_gamePixelHeight)-SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) + 1;

	// Bottom row.
	TextRendering::DrawTextAt(renderer, std::to_string(static_cast<int>(m_roundTimer.GetTimeRemaining())), { 170, bottomRowY});
	TextRendering::DrawTextAt(renderer, std::to_string(static_cast<int>(m_player.GetScore())), { 118, bottomRowY });
	TextRendering::DrawTextAt(renderer, std::to_string(static_cast<int>(m_player.GetCombo())), { 192, bottomRowY });
	TextRendering::DrawTextAt(renderer, std::to_string(static_cast<int>(m_player.GetAmmo())), { 30, bottomRowY });


	if (!m_newWaveTextTimer.HasTimerLapsed()) {
		TextRendering::DrawCenteredText(renderer, "Wave " + std::to_string(m_waveNumber));
	}

}


bool Game::AreEnemiesAlive() const {
	for (auto enemyPointer : m_enemies) {
		if (enemyPointer) {
			return true;
		}
	}

	return false;
}

void Game::SpawnNextWave()
{
	m_waveNumber++;

	// Enemies per wave:
	// Wave 1    : 1
	// Wave 2,3  : 2
	// Wave 4,5  : 3
	// Wave 6,7  : 4
	// Wave 8+   : 5
	int enemiesToSpawn = std::min(5, 1 + (m_waveNumber / 2));

	std::vector<Vector2Int> spawnPoints{ m_level.GetRandomSpawnPoints(enemiesToSpawn) };

	for (int i = 0; i < spawnPoints.size(); i++)
	{
		// m_enemies[] must be nullptr else we risk a memory leak!
		if (m_enemies[i]) {
			std::cout << "Error, an enemy isstill alive when a new wave is being spawned. This must not happen!\n";
			continue;
		}
		m_enemies[i] = new Enemy{ m_renderer, &m_level, spawnPoints[i] };
	}

	m_newWaveTextTimer.Restart();
}

void Game::Reset() {

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
