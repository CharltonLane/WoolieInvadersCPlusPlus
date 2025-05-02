#include "game.h"

void Game::HandleInput(const SDL_Event* event)
{
	m_player.HandleInput(event);
}

void Game::Update(const float dt) {
	m_player.Update(dt);
}

void Game::Render(SDL_Renderer* renderer) const {
	m_player.Render(renderer);

	m_enemy.Render(renderer);
}