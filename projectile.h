#pragma once
#include "gridEntity.h"
#include "timer.h"

class Projectile : public GridEntity
{
public:

	Projectile(SDL_Renderer* renderer, LevelGrid* level, Vector2Int gridPosition, Vector2 worldPosition, FacingDirection facingDirection)
		: GridEntity{ renderer, level, gridPosition }
	{
		m_projectileTexture = Sprite::LoadImage(renderer, "images/hand.png");
		m_sprite.SetTexture(m_projectileTexture);
		m_sprite.SetImageSize({ 8.0f, 8.0f });

		m_worldPosition = worldPosition;
		m_facingDirection = facingDirection;

		m_desiredMovement = CalculateDesiredMovementFromFacingDirection();

		m_movementSpeed = 6;
	}

	void Update(float dt) override;

private:
	SDL_Texture* m_projectileTexture{ nullptr };
	Timer m_spinTimer{ 0.08f };
};

