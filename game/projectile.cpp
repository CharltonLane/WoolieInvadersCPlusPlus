#include "projectile.h"

void Projectile::Update(float dt) {
	CalculateDesiredDirection();


	if (IsMovingBetweenSpaces()) {
		ContinueCurrentMovement(dt);
		CalculateFacingDirection(m_currentMovementDirection);
	}
	else {
		if (!AttemptMovement(m_desiredMovement)) {
			m_hasHitWall = true;
		};
		CalculateFacingDirection(m_desiredMovement);
	}


	m_sprite.SetWorldPosition(m_worldPosition);

	// Update spin of the sprite.
	m_spinTimer.Tick(dt);

	if (m_spinTimer.HasTimerLapsed()) {
		m_spinTimer.Restart();
		m_sprite.SetRotation(m_sprite.GetRotation() + 90);
	}
}