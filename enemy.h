#pragma once
#include "gridEntity.h"

class Enemy : public GridEntity
{
public:
	Enemy() = default;

	Enemy(SDL_Renderer* renderer, Vector2Int gridPosition, const std::string& spriteFilePath)
		: GridEntity{ renderer, gridPosition, spriteFilePath }
	{}
};

