#pragma once
#include "gridEntity.h"

class Enemy : public GridEntity
{
public:
	Enemy() = default;

	Enemy(SDL_Renderer* renderer, Vector2Int gridPosition)
		: GridEntity{ renderer, gridPosition }
	{
		m_sprite = Sprite{ renderer, "images/enemy/enemyDown.png" };
	}
};

