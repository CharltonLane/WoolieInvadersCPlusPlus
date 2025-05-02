#include "gridEntity.h"
#include <iostream>

void GridEntity::HandleInput(const SDL_Event* event) {


	if (m_isPlayer) {
		if (event->type == SDL_EVENT_KEY_DOWN) {
			if (event->key.repeat) {
				// Ignore repeats caused by holding down the key.
				return;
			}

			if (event->key.key == SDLK_W) {
				std::cout << "Got W key down!" << "\n";
				m_desiredMovement.SetY(-1);
			}else if (event->key.key == SDLK_A) {
				std::cout << "Got A key down!" << "\n";
				m_desiredMovement.SetX(-1);
			}
			else if (event->key.key == SDLK_S) {
				std::cout << "Got S key down!" << "\n";
				m_desiredMovement.SetY(1);
			}
			else if (event->key.key == SDLK_D) {
				std::cout << "Got D key down!" << "\n";
				m_desiredMovement.SetX(1);
			}
		}
		else if (event->type == SDL_EVENT_KEY_UP) {
			if (event->key.key == SDLK_W) {
				std::cout << "Got W key up!" << "\n";
				m_desiredMovement.SetY(0);
			}
			else if (event->key.key == SDLK_A) {
				std::cout << "Got A key up!" << "\n";
				m_desiredMovement.SetX(0);
			}
			else if (event->key.key == SDLK_S) {
				std::cout << "Got S key up!" << "\n";
				m_desiredMovement.SetY(0);
			}
			else if (event->key.key == SDLK_D) {
				std::cout << "Got D key up!" << "\n";
				m_desiredMovement.SetX(0);
			}
		}
	}
}

void GridEntity::Update(const float dt) {
	
	MoveInDirection(m_desiredMovement);
	UpdateWorldPosition(dt);

	m_sprite.SetPosition(m_worldPosition);
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

inline bool GridEntity::MoveInDirection(Vector2Int direction) {
	// If we are stopped on a tile, we can try to move in the given direction.
	// Return true if we successfully start moving, false if blocked or already moving.

	// If we're already moving, abort.


	// TODO: If there is a solid wall in that direction, abort.

	m_targetGridPosition = m_currentGridPosition += direction;

	return true;
}
