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
