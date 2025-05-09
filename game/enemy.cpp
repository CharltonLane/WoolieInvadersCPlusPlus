#include "enemy.h"
#include "random.h"

void Enemy::CalculateDesiredDirection()
{
	if (!IsMovingBetweenSpaces()) {
		m_desiredMovement = GetRandomUnobstructedDirection();
	}
}

Vector2Int Enemy::GetRandomUnobstructedDirection() const {
	// From out current position, check each direction randomly. 
	// Return one that's unobstructed, or current position if all obstructed.

	std::vector<Vector2Int> directions
	{ 
		Vector2Int{1,0}, 
		Vector2Int{0,1},
		Vector2Int{-1,0},
		Vector2Int{0,-1} 
	};
	std::mt19937 r = Random::generate();
	std::shuffle(directions.begin(), directions.end(), r);

	while (directions.size() > 0) {
		Vector2Int directionChoice{ directions.back() };

		if (m_level->IsTileSolid(m_currentGridCell + directionChoice)) {
			directions.pop_back();
		}
		else {
			return directionChoice;
		}
	}

	return Vector2Int::zero;
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