#pragma once
#include "sprite.h"
#include "vector2.h"



class GridEntity
{
	// This is an entity such as the player or an enemy that is locked to the grid for movement.

	enum class FacingDirection {
		North,
		East,
		South,
		West
	};

private:
	FacingDirection _facingDirection{ FacingDirection::North };
	Sprite m_sprite{};

	Vector2Int m_currentGridPosition{};
	Vector2Int m_targetGridPosition{};

	float m_movementSpeed{ 1 }; // Tiles per second.

public:
	GridEntity() = default;

	GridEntity(SDL_Renderer* renderer, Vector2Int gridPosition, const std::string& spriteFilePath)
		: m_currentGridPosition{ gridPosition }
		, m_targetGridPosition{ gridPosition }
		, m_sprite{ Sprite{ renderer, spriteFilePath } }
	{}

	void Update() {
		m_sprite.SetPosition(m_currentGridPosition);
	}

	void Render(SDL_Renderer* renderer) const;

	bool MoveInDirection(Vector2Int direction) {
		// If we are stopped on a tile, we can try to move in the given direction.
		// Return true if we successfully start moving, false if blocked or already moving.

		// If we're already moving, abort.


		// TODO: If there is a solid wall in that direction, abort.


	}
};


