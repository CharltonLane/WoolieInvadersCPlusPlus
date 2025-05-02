#pragma once
#include "gridEntity.h"
#include "vector2.h"

class Game {
private:
	GridEntity m_player{};
	GridEntity m_enemy{};

public:
	Game() = default;

	Game(SDL_Renderer* renderer)
		: m_player{ renderer, Vector2Int{10, 10}, "images/player/playerDown.png" }
		, m_enemy{ renderer, Vector2Int{8, 10}, "images/enemy/enemyRight.png" }
	{

	}

	void Update();
	void Render(SDL_Renderer* renderer) const;
};

