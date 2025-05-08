#include "enemy.h"
#include "random.h"

void Enemy::CalculateDesiredDirection()
{
	int directionChoice = Random::get(0, 4);

	FacingDirection direction = static_cast<FacingDirection>(directionChoice);
	switch (direction)
	{
	case FacingDirection::North:
		m_desiredMovement.SetY(-1);
		m_desiredMovement.SetX(0);
		break;
	case FacingDirection::East:
		m_desiredMovement.SetY(0);
		m_desiredMovement.SetX(1);
		break;
	case FacingDirection::South:
		m_desiredMovement.SetY(1);
		m_desiredMovement.SetX(0);
		break;
	case FacingDirection::West:
		m_desiredMovement.SetY(0);
		m_desiredMovement.SetX(-1);
		break;
	default:
		break;
	}
}

void Enemy::Update(float dt)
{
	if (!m_isAlive) {
		return;
	}

	GridEntity::Update(dt);

	// Update sprite texture.
	switch (m_facingDirection)
	{
	case GridEntity::FacingDirection::North:
		m_sprite.SetTexture(m_northTexture);
		break;
	case GridEntity::FacingDirection::East:
		m_sprite.SetTexture(m_eastTexture);
		break;
	case GridEntity::FacingDirection::South:
		m_sprite.SetTexture(m_southTexture);
		break;
	case GridEntity::FacingDirection::West:
		m_sprite.SetTexture(m_westTexture);
		break;
	default:
		break;
	}

}

void Enemy::Kill() {
	m_isAlive = false;
	Mix_PlayChannel(-1, m_hitMarkerSFX, 0);
}