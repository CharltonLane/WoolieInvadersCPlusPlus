#pragma once
#include <iostream>
#include "appState.h"
#include "sprite.h"
#include "uiButton.h"
#include "textRendering.h"
#include "appState.h"

class Menu
{

private:
	Sprite m_mainMenuHeader{};
	Sprite m_mainMenuBackground{};
	Sprite m_helpScreenBackground{};
	Sprite m_deathScreenBackground{};

	bool m_escapePressed{ false };
	bool m_leftMouseClicked{ false };
	Vector2 m_mouseScreenPosition{}; // Screen space, not pixel art pixel space.

	UIButton m_playGameButton{};
	UIButton m_helpButton{};
	UIButton m_quitGameButton{};

	UIButton m_deathScreenDoneButton{};
	UIButton m_helpScreenDoneButton{};

public:
	Menu() = default;

	Menu(SDL_Renderer* renderer)
		: m_mainMenuHeader{ renderer, "images/menu/header.png" }
		, m_mainMenuBackground{ renderer, "images/menu/menuBGWide.png" }
		, m_helpScreenBackground{ renderer, "images/menu/menuHelpBG.png" }
		, m_deathScreenBackground{ renderer, "images/menu/gameOverScreen.png" }
	{

		m_playGameButton = { renderer, SDL_FRect{SpaceConversion::g_gamePixelWidth / 2 - 30,80,60,20}, "images/menu/buttonPlay.png", "images/menu/buttonPlayHover.png" };
		m_helpButton = { renderer, SDL_FRect{SpaceConversion::g_gamePixelWidth / 2 - 30,100,60,20}, "images/menu/buttonHelp.png", "images/menu/buttonHelpHover.png" };
		m_quitGameButton = { renderer, SDL_FRect{SpaceConversion::g_gamePixelWidth / 2 - 30,120,60,20}, "images/menu/buttonQuit.png", "images/menu/buttonQuitHover.png" };

		m_deathScreenDoneButton = { renderer, SDL_FRect{SpaceConversion::g_gamePixelWidth / 2 - 30,150,60,20}, "images/menu/buttonDone.png", "images/menu/buttonDoneHover.png" };
		m_helpScreenDoneButton = { renderer, SDL_FRect{SpaceConversion::g_gamePixelWidth / 2 - 30,150,60,20}, "images/menu/buttonDone.png", "images/menu/buttonDoneHover.png" };

		// Centered on screen.
		// TODO: Use non-magic numbers.
		Vector2Int deathBackgroundSize{ 128 ,128 };
		m_deathScreenBackground.SetImageSize(deathBackgroundSize);
		m_deathScreenBackground.SetScreenPosition({ (SpaceConversion::g_gamePixelWidth / 2) - deathBackgroundSize.x() / 2, SpaceConversion::g_gamePixelHeight / 2 - deathBackgroundSize.y() / 2 });

		Vector2Int mainMenuHeaderSize{ 256 ,32 };
		m_mainMenuHeader.SetImageSize(mainMenuHeaderSize);
		m_mainMenuHeader.SetScreenPosition({ (SpaceConversion::g_gamePixelWidth / 2) - mainMenuHeaderSize.x() / 2 , 16});

		// Full screen help image.
		m_helpScreenBackground.SetImageSize({ SpaceConversion::g_gamePixelWidth, SpaceConversion::g_gamePixelHeight });

		m_mainMenuBackground.SetImageSize({ SpaceConversion::g_gamePixelWidth , SpaceConversion::g_gamePixelHeight });
	}

	void HandleInput(const SDL_Event* event);
	GameState Update(GameState gameState);
	void Render(SDL_Renderer* renderer, const AppState& appState) const;
};

