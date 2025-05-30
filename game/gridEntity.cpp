#include <iostream>
#include "gridEntity.h"
#include "vector2Int.h"
#include "spaceConversion.h"


Vector2Int GridEntity::GetCurrentGridCell() const {
	return m_currentGridCell;
}

void GridEntity::Update(const float dt) {

	m_desiredMovement = CalculateDesiredDirection();

	if (IsMovingBetweenSpaces()) {
		//std::cout << "Moving between spaces" << "\n";
		ContinueCurrentMovement(dt);
		CalculateFacingDirection(m_currentMovementDirection);
	}
	else {
		//std::cout << "Trying to move" << m_desiredMovement.x() << ", " << m_desiredMovement.y() << "\n";
		AttemptMovement(m_desiredMovement);
		CalculateFacingDirection(m_desiredMovement);
	}

	m_sprite.SetWorldPosition(m_worldPosition);
}

void GridEntity::CalculateFacingDirection(Vector2Int direction)
{
	if (direction.x() < 0) {
		m_facingDirection = FacingDirection::West;
	}
	else if (direction.x() > 0) {
		m_facingDirection = FacingDirection::East;
	}
	else if (direction.y() < 0) {
		m_facingDirection = FacingDirection::North;
	}
	else if (direction.y() > 0) {
		m_facingDirection = FacingDirection::South;
	}
	// Else we leave it as it is.
	//std::cout << "Facing: " << static_cast<int>(m_facingDirection) << "\n";
}

Vector2Int GridEntity::CalculateDesiredMovementFromFacingDirection()
{
	switch (m_facingDirection)
	{
	case GridEntity::FacingDirection::North:
		return { 0, -1 };
	case GridEntity::FacingDirection::East:
		return { 1, 0 };
	case GridEntity::FacingDirection::South:
		return { 0, 1 };
	case GridEntity::FacingDirection::West:
		return { -1, 0 };
	default:
		break;
	}
	return { 0,0 };
}


void GridEntity::UpdateWorldPosition(const float dt) {
	if (m_targetGridCell != m_currentGridCell) {

		Vector2 delta = (Vector2{ m_desiredMovement }) * (m_movementSpeed * static_cast<float>(dt));
		//std::cout << "Starting with : (" << m_worldPosition.x() << ", " << m_worldPosition.y() << ")\n";
		//std::cout << "Movement this frame: " << delta.x() << ", " << delta.y() << "\n";
		m_worldPosition += delta;
	}
	//m_currentGridPosition = m_targetGridPosition;

}

void GridEntity::SetPosition(const Vector2Int& position) {
	m_currentGridCell = position;
	m_targetGridCell = position;
	m_worldPosition = position;
	m_currentMovementDirection = Vector2Int::zero;
}

void GridEntity::Render(SDL_Renderer* renderer) const {
	m_sprite.Render(renderer, SpaceConversion::g_cameraPosition);
}

Vector2Int GridEntity::CalculateDesiredDirection() { return { 0,0 }; }

bool GridEntity::IsDirectionWalkable(Vector2Int direction) {
	// Take the current position and direction to find the target cell.
	Vector2Int targetCell = m_currentGridCell + direction;

	// Check if the target cell is solid or not.
	// Return true if not solid (i.e. the cell is walkable).
	return !m_level->IsTileSolid(targetCell);
}

bool GridEntity::IsMovingBetweenSpaces() {
	return (m_currentMovementDirection != Vector2Int::zero) && (m_targetGridCell != m_currentGridCell);
}

bool GridEntity::AttemptMovement(const Vector2Int direction) {
	// Try to move in the given direction. 
	// True if possible, false otherwise.

	// See if we want to start moving.
	if (direction != Vector2Int::zero) {
		//std::cout << "Looking to move from " << m_currentGridCell.x() << ", " << m_currentGridCell.y() << " with direction " << m_desiredMovement.x() << ", " << m_desiredMovement.y() << " \n";
		// If both x and y are held, favour X. No particular reason, just need to choose one.
		Vector2Int cleanDesiredMovement{};
		if (direction.x() != 0 && direction.y() != 0) {
			cleanDesiredMovement = Vector2Int(direction.x(), 0);
		}
		else {
			cleanDesiredMovement = direction;
		}

		if (IsDirectionWalkable(cleanDesiredMovement)) {
			m_targetGridCell = m_currentGridCell + cleanDesiredMovement;
			m_currentMovementDirection = cleanDesiredMovement;
			//std::cout << "Direction is walkable, so moving from " << m_currentGridCell << " to " << m_targetGridCell << "With direction " << m_currentMovementDirection << " \n";
			return true;
		}
		else {
			//	std::cout << "Not walkable, ignoring direction " << m_desiredMovement.x() << ", " << m_desiredMovement.y() << " \n";
			return false;
		}

	}
	return false;
}

void GridEntity::ContinueCurrentMovement(const float dt) {
	// If we are stopped on a tile, we can try to move in the given direction.
	// Return true if we successfully start moving, false if blocked or already moving.

	// If we're already moving continue movement.
	if ((m_currentMovementDirection != Vector2Int::zero)) {

		// Continue moving towards target position.
		if (m_currentMovementDirection.x() != 0) {
			float newX = m_worldPosition.x() + m_currentMovementDirection.x() * m_movementSpeed * dt;
			if ((m_currentMovementDirection.x() > 0 && newX > m_targetGridCell.x())
				|| (m_currentMovementDirection.x() < 0 && newX < m_targetGridCell.x())) {
				// We've made it.
				m_worldPosition.SetX(static_cast<float>(m_targetGridCell.x()));
				m_currentMovementDirection = Vector2Int::zero;
				m_currentGridCell = m_targetGridCell;
			}
			else {
				// Keep moving!
				m_worldPosition.SetX(newX);
			}
		}
		else if (m_currentMovementDirection.y() != 0) {
			float newY = m_worldPosition.y() + m_currentMovementDirection.y() * m_movementSpeed * dt;
			if ((m_currentMovementDirection.y() > 0 && newY > m_targetGridCell.y())
				|| m_currentMovementDirection.y() < 0 && newY < m_targetGridCell.y()) {
				// We've made it.
				m_worldPosition.SetY(static_cast<float>(m_targetGridCell.y()));
				m_currentMovementDirection = Vector2Int::zero;
				m_currentGridCell = m_targetGridCell;
			}
			else {
				// Keep moving!
				m_worldPosition.SetY(newY);
			}
		}
	}
}
