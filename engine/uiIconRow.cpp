#include "uiIconRow.h"

void UIIconRow::Render(SDL_Renderer* renderer) const {
	if (m_sprites.size() < m_iconsToShow) {
		std::cout << "Not enough icons!\n";
		return;
	}
	auto iconsToShow = static_cast<size_t>(m_iconsToShow);
	for (size_t i = 0; i < iconsToShow; i++)
	{
		m_sprites[i]->Render(renderer);
	}
}

void UIIconRow::SetIconsToShow(int count) {
	m_iconsToShow = count;
	int currentSpriteCount{ static_cast<int>(m_sprites.size()) };
	if (currentSpriteCount < count) {
		int spritesToAdd{ count - currentSpriteCount };
		for (int i = 0; i < spritesToAdd; i++)
		{
			AddNewSprite();
		}
	}
}
