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

		m_movementSpeed = 2;
	}

	void CalculateDesiredDirection() override;

	void Kill() { m_isAlive = false; }
	bool IsAlive() const { return m_isAlive; }

	void Update(float dt) override;

private:
	bool m_isAlive{ true };
};

