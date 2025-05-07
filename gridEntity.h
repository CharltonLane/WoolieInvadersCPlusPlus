#pragma once
#include <cmath>
#include "sprite.h"
#include "vector2.h"
#include "vector2Int.h"
#include "levelGrid.h"


class GridEntity
{
	// This is an entity such as the player or an enemy that is locked to the grid for movement.

private:

	Vector2Int m_currentGridCell{}; // In world space.
	Vector2Int m_targetGridCell{}; // In world space.

protected:

	enum class FacingDirection {
		North,
		East,
		South,
		West
	};

	Vector2Int m_currentMovementDirection{};

	SDL_Renderer* m_renderer{ nullptr };

	LevelGrid* m_level;

	FacingDirection m_facingDirection{ FacingDirection::North };
	Sprite m_sprite{};
	Vector2Int m_desiredMovement{};
	float m_movementSpeed{ 4 }; // Tiles per second.
	Vector2 m_worldPosition; // Actual position in world space. Can be between grid cells.

	void SetPosition(Vector2Int position) {
		m_currentGridCell = position;
		m_targetGridCell = position;
		m_worldPosition = position;
		m_currentMovementDirection = Vector2Int::zero;
	}

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

	void CalculateFacingDirection(Vector2Int direction);
	Vector2Int CalculateDesiredMovementFromFacingDirection();

	virtual void Render(SDL_Renderer* renderer) const;

	virtual void CalculateDesiredDirection();
	bool AttemptMovement(Vector2Int direction);
	bool IsDirectionWalkable(Vector2Int direction);
	bool IsMovingBetweenSpaces() {
		return (m_currentMovementDirection != Vector2Int::zero) && (m_targetGridCell != m_currentGridCell);
	}

	bool ContinueCurrentMovement(const float dt);
	void UpdateWorldPosition(const float dt);

	Vector2Int FindActiveTile() const {
		// Looks at where this entity is in world space and finds the closest tile.
		// Useful for collisions. Makes it feel more fair by finding which tile an entity is "mostly" on, rather than the one they are going to or the one they were on.

		return { static_cast<int>(std::round(m_worldPosition.x())), static_cast<int>(std::round(m_worldPosition.y())) };
	}

	bool IsCollidingWith(const GridEntity& other) const {
		// Check if this grid entity and the other are colliding.
		return FindActiveTile() == other.FindActiveTile();
	}

};


