#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <vector>
#include "gridEntity.h"
#include "timer.h"
#include "projectile.h"
#include "enemy.h"

class Player : public GridEntity
{
private:

	Vector2Int m_startingPosition{};

	// Player health.
	int m_maxHealth{ 5 };
	int m_gameStartHealth{ 3 };

	int m_health{ m_gameStartHealth };

	// Player ammo.
	int m_maxAmmo{ 6 };

	int m_ammo{ m_maxAmmo };
	Timer m_ammoRegenTimer{ 1.5f }; // 1.5 seconds to regen 1 ammo.
	std::vector<Projectile*> m_projectiles;

	// Player invincibility after being hit.
	Timer m_invincibilityTimer{ 3, 0, false }; // 3 seconds of invincibility after taking damage.

	bool m_isNorthInput{ false };
	bool m_isEastInput{ false };
	bool m_isSouthInput{ false };
	bool m_isWestInput{ false };

	bool m_isAttackInputTrigger{ false };

	// Player textures.
	SDL_Texture* m_northTexture{ nullptr };
	SDL_Texture* m_eastTexture{ nullptr };
	SDL_Texture* m_southTexture{ nullptr };
	SDL_Texture* m_westTexture{ nullptr };

	// Invincibility sprite.
	Sprite m_invincibilitySprite{};

	Projectile* CreateProjectile();
	void TrackProjectile(Projectile* newProjectile);

	// Score and combo.
	int m_score{ 0 };
	int m_combo{ 1 };
	int m_maxCombo{ 10 };

	// Audio.
	Mix_Chunk* m_takeDamageSFX{ nullptr };

public:
	Player() = default;

	Player(SDL_Renderer* renderer, LevelGrid* level, Vector2Int gridPosition)
		: GridEntity{ renderer, level, gridPosition }
		, m_projectiles(10)
		, m_invincibilitySprite{ renderer, "images/shield.png" }
		, m_startingPosition{ gridPosition }
		, m_takeDamageSFX{ Mix_LoadWAV("audio\\takeDamage.wav") }
	{
		// Load player textures.
		m_northTexture = Sprite::LoadImage(renderer, "images/player/playerNorth.png");
		m_eastTexture = Sprite::LoadImage(renderer, "images/player/playerEast.png");
		m_southTexture = Sprite::LoadImage(renderer, "images/player/playerSouth.png");
		m_westTexture = Sprite::LoadImage(renderer, "images/player/playerWest.png");

		m_sprite.SetTexture(m_northTexture);
	}

	void CalculateDesiredDirection() override;

	void HandleInput(const SDL_Event* event);
	void Render(SDL_Renderer* renderer) const override;
	void Update(float dt) override;
	void UpdateProjectiles(float dt, std::vector<Enemy*>& enemies);

	void AddHealth(int healthToAdd);
	void TakeDamage();

	bool IsAlive() const { return m_health > 0; }
	bool IsInvincible() const { return !m_invincibilityTimer.HasTimerLapsed(); }
	int GetHealth() const { return m_health; }

	int GetScore() const { return m_score; }
	int GetCombo() const { return m_combo; }
	bool IsMaxCombo() const { return m_combo == m_maxCombo; }
	int GetAmmo() const { return m_ammo; }

	void RecordKill(int points) {
		m_score += m_combo * points;
		if (m_combo < m_maxCombo) {
			m_combo++;
		}
	}

	void Reset() {
		// Move back to starting position.
		SetPosition(m_startingPosition);

		// Reset player attributes.
		m_health = m_gameStartHealth;
		m_ammo = m_maxAmmo;
		m_invincibilityTimer.SetTimer(0);
		m_score = 0;
		m_combo = 1;

		// Clear inputs.
		m_isNorthInput = false;
		m_isEastInput = false;
		m_isSouthInput = false;
		m_isWestInput = false;
		m_isAttackInputTrigger = false;

		// Destroy projectiles.
		for (auto& projectile : m_projectiles)
		{
			if (projectile) {
				delete projectile;
				projectile = nullptr;
			}
		}
	}
};

