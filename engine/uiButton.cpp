#include "uiButton.h"
#include "spaceConversion.h"

bool UIButton::IsWithinButton(const Vector2& screenPosition, bool click) const {
	Vector2 pixelSpacePosition = SpaceConversion::ScreenToPixel(screenPosition);

	bool isWithin = (pixelSpacePosition.x() >= m_rect.x && pixelSpacePosition.x() <= m_rect.x + m_rect.w)
		&& (pixelSpacePosition.y() >= m_rect.y && pixelSpacePosition.y() <= m_rect.y + m_rect.h);

	if (isWithin && click) {
		if (m_clickSFX) {
			Mix_PlayChannel(-1, m_clickSFX, 0);
		}
	}
	return isWithin;
}

void UIButton::Update(const Vector2& mousePosition) {
	if (IsWithinButton(mousePosition)) {
		m_buttonSprite.SetTexture(m_hoverTexture, false);
	}
	else {
		m_buttonSprite.SetTexture(m_standardTexture, false);
	}
}

void UIButton::Render(SDL_Renderer* renderer) const {
	m_buttonSprite.Render(renderer);
}
