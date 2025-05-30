#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <SDL3/SDL.h>
#include "game.h"
#include "spaceConversion.h"
#include "appState.h"
#include "textRendering.h"
#include "saveData.h"

void Game::StartGame() {

	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
	m_ingameMusic = Mix_LoadMUS("audio/downdown.mp3");
	if (m_ingameMusic) {
		Mix_PlayMusic(m_ingameMusic, -1);
	}
	else {
		printf("Music is null %s\n", SDL_GetError());
	}

	SaveData::ReadHighscoreFromDisk();
}

void Game::EndGame() {
	// Fade music over 3 seconds.
	Mix_FadeOutMusic(3000);


	// Write highscore to disk.
	if (m_gameOverScore > SaveData::g_highscore) {
		SaveData::WriteHighscoreToDisk(m_gameOverScore);
	}

	// Game over sound.

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

	// Play a ticking sound when low on time.
	if (!m_lowOnTime && m_roundTimer.GetTimeRemaining() <= 10.0f) {
		m_tickChannel = Mix_PlayChannel(-1, m_clockTickSFX, -1);
		m_lowOnTime = true;
	}
	if (m_lowOnTime && m_roundTimer.GetTimeRemaining() > 10.0f) {
		Mix_HaltChannel(m_tickChannel);
		m_lowOnTime = false;
	}

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
				enemyPointer = nullptr;
			}
		}
	}


	// See if the player is dead.
	if (!m_player.IsAlive()) {
		std::cout << "GAME OVER! No health!" << "\n";
		m_gameOverReason = "You died!";
		Mix_PlayChannel(-1, m_gameOverSFX, 0);
		Reset();
		return GameState::DeathScreen;
	}
	// See if the player has run out of time.
	if (m_roundTimer.HasTimerLapsed()) {
		std::cout << "GAME OVER! Out of time!" << "\n";
		m_gameOverReason = "Out of time!";
		Mix_PlayChannel(-1, m_gameOverSFX, 0);
		Reset();
		return GameState::DeathScreen;
	}

	if (!AreEnemiesAlive()) {
		SpawnNextWave();
		m_roundTimer.AddTime(m_secondsAddedOnNewRound);
		if (m_waveNumber % 2 == 0) {
			m_player.AddHealth(1);
		}
	}

	m_newWaveTextTimer.Tick(dt);


	m_handIcons.SetIconsToShow(m_player.GetAmmo());
	m_heartIcons.SetIconsToShow(m_player.GetHealth());
	m_enemyIcons.SetIconsToShow(1); // Not showing list of enemies, just 1 icon now and using text for number.

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
	m_shopLevelBackground.Render(renderer, SpaceConversion::g_cameraPosition);

	// Render entities.
	m_player.Render(renderer);
	for (const auto& enemyPointer : m_enemies)
	{
		if (enemyPointer) {
			enemyPointer->Render(renderer);
		}
	}

	// New wave text.
	if (!m_newWaveTextTimer.HasTimerLapsed()) {
		TextRendering::SetTextColor(TextRendering::g_colorYellow);
		TextRendering::DrawCenteredText(renderer, "Wave " + std::to_string(m_waveNumber));
		TextRendering::SetTextColor(TextRendering::g_colorWhite);
	}

	// Render HUD.
	m_hudBackground.Render(renderer);

	float bottomRowY = SpaceConversion::g_gamePixelHeight - 10;
	float topRowY = SpaceConversion::g_gamePixelHeight - 22;

	// Top row.
	m_handIcons.Render(renderer);
	m_heartIcons.Render(renderer);
	m_enemyIcons.Render(renderer);
	TextRendering::DrawTextAt(renderer, "x", { 236.0f, topRowY });
	TextRendering::DrawTextAt(renderer, GetEnemiesAliveCount(), { 236.0f + SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE, topRowY });

	// Bottom row.
	TextRendering::DrawTextAt(renderer, static_cast<int>(m_roundTimer.GetTimeRemaining()), { 121, bottomRowY });
	TextRendering::DrawTextAt(renderer, m_player.GetScore(), { 172, bottomRowY });
	TextRendering::DrawTextAt(renderer, m_waveNumber, { 84, bottomRowY });

	if (m_player.IsMaxCombo()) {
		TextRendering::SetTextColor(TextRendering::g_colorYellow);
	}	
	TextRendering::DrawTextAt(renderer, "x", { 236.0f, bottomRowY });
	TextRendering::DrawTextAt(renderer, m_player.GetCombo(), { 236.0f + SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE, bottomRowY });
	TextRendering::SetTextColor(TextRendering::g_colorWhite);

}

int Game::GetEnemiesAliveCount() const {
	int count{ 0 };
	for (const auto& enemyPointer : m_enemies) {
		if (enemyPointer) {
			count++;
		}
	}
	return count;
}

bool Game::AreEnemiesAlive() const {
	return GetEnemiesAliveCount() > 0;
}

void Game::SpawnNextWave()
{
	m_waveNumber++;

	// Enemies per wave:
	// Wave 1    : 1
	// Wave 2,3  : 2
	// Wave 4,5  : 3
	// Wave 6,7  : 4
	// Wave 8    : 5
	// Wave 10+  : 6
	int enemiesToSpawn = std::min(6, 1 + (m_waveNumber / 2));

	std::vector<Vector2Int> spawnPoints{ m_level.GetRandomSpawnPoints(enemiesToSpawn) };

	for (int i = 0; i < spawnPoints.size(); i++)
	{
		// m_enemies[] must be nullptr else we risk a memory leak!
		if (m_enemies[i]) {
			std::cout << "Error, an enemy isstill alive when a new wave is being spawned. This must not happen!\n";
			continue;
		}
		m_enemies[i] = std::move(std::make_unique<Enemy>(m_renderer, &m_level, spawnPoints[i]));
	}

	m_newWaveTextTimer.Restart();
}

void Game::Reset() {

	m_gameOverScore = m_player.GetScore();

	m_escapeKeyPressed = false;
	m_roundTimer.SetTimerOneShot(m_roundTimerStartDuration);
	m_waveNumber = 0;

	m_player.Reset();
	DeleteAllEnemies();

	if (m_lowOnTime) {
		Mix_HaltChannel(m_tickChannel);
		m_lowOnTime = false;
	}
}

void Game::DeleteAllEnemies()
{
	for (auto& enemy : m_enemies)
	{
		if (enemy) {
			enemy = nullptr;
		}
	}
	// We don't clear the m_enemies array here as it's got a fixed size as we know the max number of enemies.
}
