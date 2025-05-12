#pragma once
#include <SDL3_mixer/SDL_mixer.h>
#include "gridEntity.h"

class Enemy : public GridEntity
{
public:
	Enemy() = default;

	Enemy(SDL_Renderer* renderer, LevelGrid* level, Vector2Int gridPosition)
		: GridEntity{ renderer, level, gridPosition }
	{
		m_movementSpeed = 2;

		m_northTexture = Sprite::LoadTexture(renderer, "images/enemy/enemyNorth.png");
		m_eastTexture = Sprite::LoadTexture(renderer, "images/enemy/enemyEast.png");
		m_southTexture = Sprite::LoadTexture(renderer, "images/enemy/enemySouth.png");
		m_westTexture = Sprite::LoadTexture(renderer, "images/enemy/enemyWest.png");

		m_sprite.SetTexture(m_northTexture);

		if (!m_hitMarkerSFX) {
			m_hitMarkerSFX = Mix_LoadWAV("audio/hitMarker.wav");
		}
	}

	~Enemy()
	{
		// Clear the current sprite texture, as we destroy them all below instead of letting the sprite handle it.
		m_sprite.SetTexture(nullptr, false);
		SDL_DestroyTexture(m_northTexture);
		SDL_DestroyTexture(m_eastTexture);
		SDL_DestroyTexture(m_southTexture);
		SDL_DestroyTexture(m_westTexture);
	}

	Vector2Int CalculateDesiredDirection() override;
	Vector2Int GetRandomUnobstructedDirection() const;
	void Kill();
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

	// Audio.
	static Mix_Chunk* m_hitMarkerSFX;
};

inline Mix_Chunk* Enemy::m_hitMarkerSFX{ nullptr };