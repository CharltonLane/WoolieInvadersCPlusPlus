#pragma once
#include <iostream>
#include "appState.h"
#include "sprite.h"
#include "uiButton.h"
#include "textRendering.h"

class Menu
{

private:
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
		: m_mainMenuBackground{ renderer, "images/menu/menuBG.png" }
		, m_helpScreenBackground{ renderer, "images/menu/menuHelpBG.png" }
		, m_deathScreenBackground{ renderer, "images/menu/gameOverBG.png" }
	{

		m_playGameButton = { renderer, SDL_FRect{200/2-30,80,60,20}, "images/menu/buttonPlay.png", "images/menu/buttonPlayHover.png" };
		m_helpButton = { renderer, SDL_FRect{200/2 - 30,100,60,20}, "images/menu/buttonHelp.png", "images/menu/buttonHelpHover.png" };
		m_quitGameButton = { renderer, SDL_FRect{200 / 2 - 30,120,60,20}, "images/menu/buttonQuit.png", "images/menu/buttonQuitHover.png" };

		m_deathScreenDoneButton = { renderer, SDL_FRect{200 / 2 - 30,120,60,20}, "images/menu/buttonDone.png", "images/menu/buttonDoneHover.png" };
		m_helpScreenDoneButton = { renderer, SDL_FRect{200 / 2 - 30,120,60,20}, "images/menu/buttonDone.png", "images/menu/buttonDoneHover.png" };
	
		// Centered on screen.
		// TODO: Use non-magic numbers.
		m_deathScreenBackground.SetImageSize({100, 100});
		m_deathScreenBackground.SetScreenPosition({(800/4/2) - 50, 600/4/2 - 50});
	}

	void HandleInput(const SDL_Event* event, GameState gameState) {

		if (event->type == SDL_EVENT_MOUSE_MOTION) {
			float x, y;
			SDL_GetMouseState(&x, &y);
			m_mouseScreenPosition.SetX(x);
			m_mouseScreenPosition.SetY(y);
			//std::cout << m_mouseScreenPosition << " Mouse pos \n";
		}
		else if (event->type == SDL_EVENT_KEY_DOWN) {
			if (event->key.repeat) {
				// Ignore repeats caused by holding down the key.
				return;
			}

			if (event->key.key == SDLK_ESCAPE) {
				m_escapePressed = true;
			}
		}

		else if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			if (event->button.button == SDL_BUTTON_LEFT) {
				m_leftMouseClicked = true;
				std::cout << "Click!" << "\n";
			}
		}


	}

	void Render(SDL_Renderer* renderer, GameState gameState) const {
		switch (gameState)
		{
		case GameState::MainMenu:
			m_mainMenuBackground.Render(renderer);
			m_playGameButton.Render(renderer);
			m_helpButton.Render(renderer);
			m_quitGameButton.Render(renderer);
			break;
		case GameState::HelpMenu:
			m_helpScreenBackground.Render(renderer);
			m_helpScreenDoneButton.Render(renderer);
			break;
		case GameState::DeathScreen:
			m_mainMenuBackground.Render(renderer);
			m_deathScreenBackground.Render(renderer);
			// TODO: Draw game info text.
			TextRendering::DrawCenteredText(renderer, "TODO!");

			m_deathScreenDoneButton.Render(renderer);
			break;
		default:
			break;
		}
	}

	GameState Update(float dt, GameState gameState) {

		GameState returnState{ gameState };

		switch (gameState)
		{
		case GameState::MainMenu:
			m_playGameButton.Update(m_mouseScreenPosition);
			m_helpButton.Update(m_mouseScreenPosition);
			m_quitGameButton.Update(m_mouseScreenPosition);
			if (m_leftMouseClicked) {
				if (m_playGameButton.IsWithinButton(m_mouseScreenPosition)) {
					std::cout << "START THE GAME!!!\n";
					returnState = GameState::Ingame;
				}
				if (m_helpButton.IsWithinButton(m_mouseScreenPosition)) {
					returnState = GameState::HelpMenu;
				}
				if (m_quitGameButton.IsWithinButton(m_mouseScreenPosition)) {
					returnState = GameState::Quit;
				}
			}
			break;
		case GameState::HelpMenu:
			m_playGameButton.Update(m_mouseScreenPosition);
			m_helpScreenDoneButton.Update(m_mouseScreenPosition);
			if (m_leftMouseClicked) {
				if (m_helpScreenDoneButton.IsWithinButton(m_mouseScreenPosition)) {
					returnState = GameState::MainMenu;
				}
			}
			if (m_escapePressed) {
				returnState = GameState::MainMenu;
			}
			break;
		case GameState::DeathScreen:
			m_deathScreenDoneButton.Update(m_mouseScreenPosition);
			if (m_leftMouseClicked) {
				if (m_deathScreenDoneButton.IsWithinButton(m_mouseScreenPosition)) {
					returnState = GameState::MainMenu;
				}
			}
			if (m_escapePressed) {
				returnState = GameState::MainMenu;
			}
			break;
		default:
			break;
		}

		m_escapePressed = false;
		m_leftMouseClicked = false;

		return returnState;
	}

};

