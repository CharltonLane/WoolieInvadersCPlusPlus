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

	Vector2 m_worldPosition; // Actual position in world space. World/Screen/Pixel space are all the same currently.

	Vector2Int m_currentGridPosition{};
	Vector2Int m_targetGridPosition{};


	float m_movementSpeed{ 10 }; // Tiles per second.

protected:
	Vector2Int m_desiredMovement{};

public:
	GridEntity() = default;

	GridEntity(SDL_Renderer* renderer, Vector2Int gridPosition, const std::string& spriteFilePath)
		: m_currentGridPosition{ gridPosition }
		, m_targetGridPosition{ gridPosition }
		, m_sprite{ Sprite{ renderer, spriteFilePath } }
	{
		m_worldPosition = gridPosition;
	}

	void Update(const float dt);

	void Render(SDL_Renderer* renderer) const;

	virtual void CalculateDesiredDirection();
	bool MoveInDirection(Vector2Int direction);
	void UpdateWorldPosition(const float dt);
};


