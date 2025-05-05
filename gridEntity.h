#pragma once
#include "sprite.h"
#include "vector2.h"
#include "levelGrid.h"


class GridEntity
{
	// This is an entity such as the player or an enemy that is locked to the grid for movement.

private:


	Vector2Int m_currentMovementDirection{};
	Vector2Int m_currentGridCell{}; // In world space.
	Vector2Int m_targetGridCell{}; // In world space.

protected:

	enum class FacingDirection {
		North,
		East,
		South,
		West
	};

	SDL_Renderer* m_renderer{ nullptr };

	LevelGrid* m_level;

	FacingDirection m_facingDirection{ FacingDirection::North };
	Sprite m_sprite{};
	Vector2Int m_desiredMovement{};
	float m_movementSpeed{ 4 }; // Tiles per second.
	Vector2 m_worldPosition; // Actual position in world space. Can be between grid cells.


public:
	GridEntity() = default;

	GridEntity([[maybe_unused]] SDL_Renderer* renderer, LevelGrid* level, Vector2Int gridPosition)
		:m_renderer{ renderer }
		, m_level{ level }
		, m_currentGridCell{ gridPosition }
		, m_targetGridCell{ gridPosition }
		, m_sprite{ Sprite{  } }
	{

		m_worldPosition = gridPosition;
	}

	Vector2Int GetCurrentGridCell() const;

	virtual void Update(const float dt);

	void CalculateFacingDirection();
	Vector2Int CalculateDesiredMovementFromFacingDirection();

	virtual void Render(SDL_Renderer* renderer) const;

	virtual void CalculateDesiredDirection();
	bool IsDirectionWalkable(Vector2Int direction);
	bool MoveInDirection(const float dt);
	void UpdateWorldPosition(const float dt);
};


