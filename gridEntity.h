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

	bool m_isPlayer{ false }; // TODO: Replace with inheritance.

	Vector2Int m_desiredMovement{};

	float m_movementSpeed{ 10 }; // Tiles per second.

public:
	GridEntity() = default;

	GridEntity(SDL_Renderer* renderer, Vector2Int gridPosition, const std::string& spriteFilePath)
		: m_currentGridPosition{ gridPosition }
		, m_targetGridPosition{ gridPosition }
		, m_sprite{ Sprite{ renderer, spriteFilePath } }
	{
		m_worldPosition = gridPosition;
	}

	void HandleInput(const SDL_Event* event);
	void Update(const double dt);

	void Render(SDL_Renderer* renderer) const;

	bool MoveInDirection(Vector2Int direction);
	void UpdateWorldPosition(const double dt);

	void SetPlayer(bool isPlayer) {
		m_isPlayer = isPlayer;
	}
};


