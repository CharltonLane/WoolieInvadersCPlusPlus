#pragma once
#include "gridEntity.h"

class Enemy : public GridEntity
{
public:
	Enemy() = default;

	Enemy(SDL_Renderer* renderer, LevelGrid* level, Vector2Int gridPosition)
		: GridEntity{ renderer, level, gridPosition }
	{
		m_sprite = Sprite{ renderer, "images/enemy/enemySouth.png" };

		m_movementSpeed = 2;

		m_northTexture = Sprite::LoadImage(renderer, "images/enemy/enemyNorth.png");
		m_eastTexture = Sprite::LoadImage(renderer, "images/enemy/enemyEast.png");
		m_southTexture = Sprite::LoadImage(renderer, "images/enemy/enemySouth.png");
		m_westTexture = Sprite::LoadImage(renderer, "images/enemy/enemyWest.png");

		m_sprite.SetTexture(m_northTexture);
	}

	void CalculateDesiredDirection() override;

	void Kill() { m_isAlive = false; }
	bool IsAlive() const { return m_isAlive; }
	int GetPoints() const { return m_pointsPerKill; }

	void Update(float dt) override;

private:
	// Directional textures.
	SDL_Texture* m_northTexture{ nullptr };
	SDL_Texture* m_eastTexture{ nullptr };
	SDL_Texture* m_southTexture{ nullptr };
	SDL_Texture* m_westTexture{ nullptr };

	bool m_isAlive{ true };
	int m_pointsPerKill{ 10 };
};

