#include "gridEntity.h"
#include <iostream>



void GridEntity::Update(const float dt) {
	
	CalculateDesiredDirection();
	MoveInDirection(dt);
	UpdateWorldPosition(dt);

	m_sprite.SetWorldPosition(m_worldPosition);
}

void GridEntity::UpdateWorldPosition(const float dt) {
	if (m_targetGridCell != m_currentGridCell) {

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

inline bool GridEntity::MoveInDirection(const float dt) {
	// If we are stopped on a tile, we can try to move in the given direction.
	// Return true if we successfully start moving, false if blocked or already moving.

	
	// See if we want to start moving.
	// TODO: Overload == on Vector2Int!
	if (!(m_currentMovementDirection != Vector2Int::zero) && m_desiredMovement != Vector2Int::zero) {
		// If both x and y are held, favour X. No particular reason, just need to choose one.
		if (m_desiredMovement.x() != 0 && m_desiredMovement.y() != 0) {
			m_currentMovementDirection = Vector2Int(m_desiredMovement.x(), 0);
		}
		else {
			m_currentMovementDirection = m_desiredMovement;
		}
		m_targetGridCell = m_currentGridCell + m_currentMovementDirection;
	}
	
	// If we're already moving continue movement.
	if (m_currentMovementDirection != Vector2Int::zero) {
		// Continue moving towards target position.
		if (m_currentMovementDirection.x() > 0) {
			float newX = m_worldPosition.x() + m_currentMovementDirection.x() * m_movementSpeed * dt;
			if (newX > m_targetGridCell.x()) {
				// We've made it.
				m_worldPosition.SetX(static_cast<float>(m_targetGridCell.x()));
				m_currentMovementDirection = Vector2Int::zero;
			}
			else {
				// Keep moving!
				m_worldPosition.SetX(newX);
			}
			return true;

		}else if (m_currentMovementDirection.x() < 0) {
			float newX = m_worldPosition.x() + m_currentMovementDirection.x() * m_movementSpeed * dt;
			if (newX < m_targetGridCell.x()) {
				// We've made it.
				m_worldPosition.SetX(static_cast<float>(m_targetGridCell.x()));
				m_currentMovementDirection = Vector2Int::zero;
			}
			else {
				// Keep moving!
				m_worldPosition.SetX(newX);
			}
			return true;
		}

		if (m_currentMovementDirection.y() > 0) {
			float newY = m_worldPosition.y() + m_currentMovementDirection.y() * m_movementSpeed * dt;
			if (newY > m_targetGridCell.y()) {
				// We've made it.
				m_worldPosition.SetY(static_cast<float>(m_targetGridCell.y()));
				m_currentMovementDirection = Vector2Int::zero;
			}
			else {
				// Keep moving!
				m_worldPosition.SetY(newY);
			}
			return true;
		}
		else if (m_currentMovementDirection.y() < 0) {
			float newY = m_worldPosition.y() + m_currentMovementDirection.y() * m_movementSpeed * dt;
			if (newY < m_targetGridCell.y()) {
				// We've made it.
				m_worldPosition.SetY(static_cast<float>(m_targetGridCell.y()));
				m_currentMovementDirection = Vector2Int::zero;
			}
			else {
				// Keep moving!
				m_worldPosition.SetY(newY);
			}
			return true;
		}
	}
	

	return true;
}
