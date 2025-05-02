#include "game.h"

void Game::Update() {
	m_player.Update();
}

void Game::Render(SDL_Renderer* renderer) const {
	m_player.Render(renderer);

	m_enemy.Render(renderer);
}