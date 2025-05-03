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

	Vector2 m_worldPosition; // Actual position in world space. Can be between grid cells.

	Vector2Int m_currentMovementDirection{};
	Vector2Int m_currentGridCell{}; // In world space.
	Vector2Int m_targetGridCell{}; // In world space.


	float m_movementSpeed{ 4 }; // Tiles per second.

protected:
	Vector2Int m_desiredMovement{};

public:
	GridEntity() = default;

	GridEntity(SDL_Renderer* renderer, Vector2Int gridPosition, const std::string& spriteFilePath)
		: m_currentGridCell{ gridPosition }
		, m_targetGridCell{ gridPosition }
		, m_sprite{ Sprite{ renderer, spriteFilePath } }
	{
		m_worldPosition = gridPosition;
	}

	void Update(const float dt);

	void Render(SDL_Renderer* renderer) const;

	virtual void CalculateDesiredDirection();
	bool MoveInDirection(const float dt);
	void UpdateWorldPosition(const float dt);
};


