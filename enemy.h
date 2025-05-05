#pragma once
#include "gridEntity.h"

class Enemy : public GridEntity
{
public:
	Enemy() = default;

	Enemy(SDL_Renderer* renderer, LevelGrid* level, Vector2Int gridPosition)
		: GridEntity{ renderer, level, gridPosition }
	{
		m_sprite = Sprite{ renderer, "images/enemy/enemyDown.png" };

		m_movementSpeed = 3;
	}

	void CalculateDesiredDirection() override;
};

