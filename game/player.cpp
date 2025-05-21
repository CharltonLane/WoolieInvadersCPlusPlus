#include <iostream>
#include <vector>
#include <SDL3_mixer/SDL_mixer.h>
#include "player.h"
#include "enemy.h"
#include "spaceConversion.h"

void Player::HandleInput(const SDL_Event* event) {


	if (event->type == SDL_EVENT_KEY_DOWN) {
		if (event->key.repeat) {
			// Ignore repeats caused by holding down the key.
			return;
		}

		if (event->key.key == SDLK_SPACE) {
			m_isAttackInputTrigger = true;
		}

		if (event->key.key == SDLK_W) {
			//std::cout << "Got W key down!" << "\n";
			m_isNorthInput = true;
		}
		else if (event->key.key == SDLK_A) {
			//std::cout << "Got A key down!" << "\n";
			m_isWestInput = true;
		}
		else if (event->key.key == SDLK_S) {
			//std::cout << "Got S key down!" << "\n";
			m_isSouthInput = true;
		}
		else if (event->key.key == SDLK_D) {
			//std::cout << "Got D key down!" << "\n";
			m_isEastInput = true;
		}
	}
	else if (event->type == SDL_EVENT_KEY_UP) {
		if (event->key.key == SDLK_W) {
			//std::cout << "Got W key up!" << "\n";
			m_isNorthInput = false;
		}
		else if (event->key.key == SDLK_A) {
			//std::cout << "Got A key up!" << "\n";
			m_isWestInput = false;
		}
		else if (event->key.key == SDLK_S) {
			//std::cout << "Got S key up!" << "\n";
			m_isSouthInput = false;
		}
		else if (event->key.key == SDLK_D) {
			//std::cout << "Got D key up!" << "\n";
			m_isEastInput = false;
		}
	}

}

void Player::TrackProjectile(Projectile* newProjectile) {
	// Dynamically create a new projectile object.

	bool foundSpace = false;
	for (auto& existingProjectile : m_projectiles)
	{
		if (existingProjectile) {
			continue;
		}
		// Found an empty space in the vector. Add new projectile here.
		foundSpace = true;

		existingProjectile = newProjectile;
		break;
	}
	if (!foundSpace) {
		m_projectiles.resize(m_projectiles.size() + 1);
		// Insert projectile at the new index.
		m_projectiles[m_projectiles.size() - 1] = newProjectile;
	}
}

Projectile* Player::CreateProjectile() {
	// Dynamically create a new projectile object.
	return new Projectile{ m_renderer, m_level, GetCurrentGridCell(), m_worldPosition, m_facingDirection };
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

	if (m_isAttackInputTrigger) {
		m_isAttackInputTrigger = false;

		if (m_ammo > 0) {
			//std::cout << "Shot projectile!" << "\n";

			TrackProjectile(CreateProjectile());

			m_ammo--;
		}
	}

	if (m_ammo < m_maxAmmo) {
		m_ammoRegenTimer.Tick(dt);

		if (m_ammoRegenTimer.HasTimerLapsed()) {
			if (m_ammo < m_maxAmmo) {
				m_ammo++;
				m_ammoRegenTimer.Restart();
			}
		}
	}


	m_invincibilityTimer.Tick(dt);
	if (IsInvincible()) {
		m_invincibilitySprite.SetWorldPosition(m_worldPosition);
	}
}

void Player::UpdateProjectiles(float dt, std::vector<std::unique_ptr<Enemy>>& enemies) {
	// Move projectiles and see if there are enemy collisions.
	for (auto& projectile : m_projectiles)
	{
		if (projectile) {
			projectile->Update(dt);

			for (auto& enemy : enemies) {
				if (enemy) {
					if (projectile->IsCollidingWith(*enemy)) {
						RecordKill(enemy->GetPoints());
						enemy->Kill();
					}
				}
			}

			if (projectile->HasHitWall()) {
				delete projectile;
				projectile = nullptr;
			}
		}
	}
}

void Player::AddHealth(int healthToAdd) {
	m_health = std::min(m_health + healthToAdd, m_maxHealth);
}

void Player::TakeDamage() {
	if (!IsInvincible()) {
		m_health--;
		m_invincibilityTimer.Restart();
		m_combo = 1;
		Mix_PlayChannel(-1, m_takeDamageSFX, 0);
		m_invincibilitySprite.SetWorldPosition(m_worldPosition);
	}
	// Otherwise we're invincible, and no damage is to be taken!
}

void Player::Render(SDL_Renderer* renderer) const
{
	m_sprite.Render(renderer, SpaceConversion::g_cameraPosition);

	// Update projectiles.
	for (auto& projectile : m_projectiles)
	{
		if (projectile) {
			//std::cout << "rendering projectile\n";
			projectile->Render(renderer);
		}
	}

	if (IsInvincible()) {
		m_invincibilitySprite.Render(renderer, SpaceConversion::g_cameraPosition);
	}
}



Vector2Int Player::CalculateDesiredDirection() {

	int x = 0;
	int y = 0;
	if (m_isNorthInput) {
		y--;
	}
	if (m_isSouthInput) {
		y++;
	}

	if (m_isWestInput) {
		x--;
	}
	if (m_isEastInput) {
		x++;
	}

	return { x, y };
}