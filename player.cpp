#include <iostream>
#include "player.h"

void Player::HandleInput(const SDL_Event* event) {

	if (event->type == SDL_EVENT_KEY_DOWN) {
		if (event->key.repeat) {
			// Ignore repeats caused by holding down the key.
			return;
		}

		if (event->key.key == SDLK_W) {
			std::cout << "Got W key down!" << "\n";
			m_isNorthInput = true;
		}
		else if (event->key.key == SDLK_A) {
			std::cout << "Got A key down!" << "\n";
			m_isWestInput = true;
		}
		else if (event->key.key == SDLK_S) {
			std::cout << "Got S key down!" << "\n";
			m_isSouthInput = true;
		}
		else if (event->key.key == SDLK_D) {
			std::cout << "Got D key down!" << "\n";
			m_isEastInput = true;
		}
	}
	else if (event->type == SDL_EVENT_KEY_UP) {
		if (event->key.key == SDLK_W) {
			std::cout << "Got W key up!" << "\n";
			m_isNorthInput = false;
		}
		else if (event->key.key == SDLK_A) {
			std::cout << "Got A key up!" << "\n";
			m_isWestInput = false;
		}
		else if (event->key.key == SDLK_S) {
			std::cout << "Got S key up!" << "\n";
			m_isSouthInput = false;
		}
		else if (event->key.key == SDLK_D) {
			std::cout << "Got D key up!" << "\n";
			m_isEastInput = false;
		}
	}

}

void Player::Update(float dt) {
	GridEntity::Update(dt);

	switch (m_facingDirection)
	{
	case GridEntity::FacingDirection::North:
		m_sprite.SetTexture(m_northTexture);
		break;
	case GridEntity::FacingDirection::East:
		m_sprite.SetTexture(m_eastTexture);
		break;
	case GridEntity::FacingDirection::South:
		m_sprite.SetTexture(m_southTexture);
		break;
	case GridEntity::FacingDirection::West:
		m_sprite.SetTexture(m_westTexture);
		break;
	default:
		break;
	}
}


void Player::Render(SDL_Renderer* renderer) const
{
	m_sprite.Render(renderer);
}



void Player::CalculateDesiredDirection() {

	int x = 0;
	int y = 0;
	if (m_isNorthInput) {
		y--;
	}
	if (m_isSouthInput) {
		y++;
	}
	m_desiredMovement.SetY(y);

	if (m_isWestInput) {
		x--;
	}
	if (m_isEastInput) {
		x++;
	}
	m_desiredMovement.SetX(x);
}