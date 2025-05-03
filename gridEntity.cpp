#include "gridEntity.h"
#include <iostream>



void GridEntity::Update(const float dt) {
	
	CalculateDesiredDirection();
	MoveInDirection(m_desiredMovement);
	UpdateWorldPosition(dt);

	m_sprite.SetWorldPosition(m_worldPosition);
}

void GridEntity::UpdateWorldPosition(const float dt) {
	if (m_targetGridPosition != m_currentGridPosition) {

		Vector2 delta = (Vector2{ m_desiredMovement }) * (m_movementSpeed * static_cast<float>(dt));
		std::cout << "Starting with : (" << m_worldPosition.x() << ", " << m_worldPosition.y() << ")\n";
		std::cout << "Movement this frame: " << delta.x() << ", " << delta.y() << "\n";
		m_worldPosition += delta;
	}
	//m_currentGridPosition = m_targetGridPosition;
	
}

void GridEntity::Render(SDL_Renderer* renderer) const {
	m_sprite.Render(renderer);
}

void GridEntity::CalculateDesiredDirection(){}

inline bool GridEntity::MoveInDirection(Vector2Int direction) {
	// If we are stopped on a tile, we can try to move in the given direction.
	// Return true if we successfully start moving, false if blocked or already moving.

	// If we're already moving, abort.


	// TODO: If there is a solid wall in that direction, abort.

	m_targetGridPosition = m_currentGridPosition += direction;

	return true;
}
