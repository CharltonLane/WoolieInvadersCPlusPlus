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
	int GetPoints() const { return m_pointsPerKill; }

	void Update(float dt) override;

	// TODO: Add enemy sprites per facing direction.

private:
	bool m_isAlive{ true };
	int m_pointsPerKill{ 10 };
};

