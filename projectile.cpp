#include "projectile.h"

void Projectile::Update(float dt) {
	GridEntity::Update(dt);

	// Update spin of the sprite.
	m_spinTimer.Tick(dt);

	if (m_spinTimer.HasTimerLapsed()) {
		m_spinTimer.Restart();
		m_sprite.SetRotation(m_sprite.GetRotation() + 90);
	}
}