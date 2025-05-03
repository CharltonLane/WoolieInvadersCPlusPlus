#pragma once
#include "gridEntity.h"
#include "vector2.h"
#include "timer.h"
#include "spaceConversion.h"

class Game {
private:
	// Entities.
	GridEntity m_player{};
	GridEntity m_enemy{};

	// Sprites.
	Sprite m_shopBackground{};
Sprite m_hudBackground{};

	// Round timer.
	float m_roundTimerStartDuration{ 30.0f };
	Timer m_roundTimer{ m_roundTimerStartDuration };

public:
	Game() = default;

	Game(SDL_Renderer* renderer)
		: m_player{ renderer, Vector2Int{4, 4}, "images/player/playerDown.png" }
		, m_enemy{ renderer, Vector2Int{8, 10}, "images/enemy/enemyRight.png" }
		, m_shopBackground { renderer, "images/world/shop.png" }
		, m_hudBackground {renderer, "images/hud/hudBG.png"}
	{
		m_player.SetPlayer(true);
		m_hudBackground.SetScreenPosition(Vector2{0, SpaceConversion::g_gamePixelHeight - m_hudBackground.GetImageSize().y()});
	}

	void HandleInput(const SDL_Event* event);
	void Update(const float dt);
	void Render(SDL_Renderer* renderer) const;
};

