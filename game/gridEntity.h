#pragma once
#include <cmath>
#include "sprite.h"
#include "vector2.h"
#include "vector2Int.h"
#include "levelGrid.h"


class GridEntity
{
	// This is an entity such as the player or an enemy that is locked to the grid for movement.

public:
	GridEntity() = default;

	GridEntity(SDL_Renderer* renderer, LevelGrid* level, Vector2Int gridPosition)
		: m_renderer{ renderer }
		, m_level{ level }
		, m_currentGridCell{ gridPosition }
		, m_targetGridCell{ gridPosition }
		, m_worldPosition{ gridPosition }
	{}

	virtual ~GridEntity() = default;

	virtual void Update(const float dt);
	virtual void Render(SDL_Renderer* renderer) const;

	void CalculateFacingDirection(Vector2Int direction);
	Vector2Int CalculateDesiredMovementFromFacingDirection();


	virtual Vector2Int CalculateDesiredDirection();
	bool AttemptMovement(Vector2Int direction);


	void ContinueCurrentMovement(const float dt);
	void UpdateWorldPosition(const float dt);

	bool IsDirectionWalkable(Vector2Int direction);
	bool IsMovingBetweenSpaces();
	Vector2Int GetCurrentGridCell() const;
	Vector2Int FindActiveTile() const {
		// Looks at where this entity is in world space and finds the closest tile.
		// Useful for collisions. Makes it feel more fair by finding which tile an entity is "mostly" on, rather than the one they are going to or the one they were on.

		return { static_cast<int>(std::round(m_worldPosition.x())), static_cast<int>(std::round(m_worldPosition.y())) };
	}

	bool IsCollidingWith(const GridEntity& other) const {
		// Check if this grid entity and the other are colliding.
		return FindActiveTile() == other.FindActiveTile();
	}


protected:

	enum class FacingDirection {
		North,
		East,
		South,
		West
	};

	SDL_Renderer* m_renderer{ nullptr };

	Vector2Int m_currentGridCell{}; // In world space.
	Vector2Int m_targetGridCell{}; // In world space.

	Vector2Int m_currentMovementDirection{};

	LevelGrid* m_level;

	FacingDirection m_facingDirection{ FacingDirection::North };
	Sprite m_sprite{};
	Vector2Int m_desiredMovement{}; // The direction this entity wants to move in.
	float m_movementSpeed{ 4 }; // Grid tiles per second.
	Vector2 m_worldPosition; // Actual position in world space. Can be between grid cells.

	void SetPosition(const Vector2Int& position);
};


