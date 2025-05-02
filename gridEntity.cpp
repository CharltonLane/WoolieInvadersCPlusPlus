#include "gridEntity.h"

void GridEntity::Render(SDL_Renderer* renderer) const {
	m_sprite.Render(renderer);
}
