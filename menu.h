#pragma once
#include "appState.h"
#include "sprite.h"

class Menu
{

private:
	Sprite m_mainMenuBackground{};
	Sprite m_helpScreenBackground{};
	Sprite m_deathScreenBackground{};

	bool m_escapePressed{ false };
	bool m_leftMouseClicked{ false };
	Vector2 m_mouseScreenPosition{}; // Screen space, not pixel art pixel space.

public:
	Menu() = default;

	Menu(SDL_Renderer* renderer)
		: m_mainMenuBackground{ renderer, "images/menu/menuBG.png" }
		, m_helpScreenBackground{ renderer, "images/menu/menuHelpBG.png" }
		, m_deathScreenBackground{ renderer, "images/menu/gameOverBG.png" }
	{
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
			}
		}


	}

	void Render(SDL_Renderer* renderer, GameState gameState) const {
		switch (gameState)
		{
		case GameState::MainMenu:
			m_mainMenuBackground.Render(renderer);
			// TODO: Draw buttons.
			break;
		case GameState::HelpMenu:
			m_helpScreenBackground.Render(renderer);
			// TODO: Draw buttons.
			break;
		case GameState::DeathScreen:
			m_deathScreenBackground.Render(renderer);
			// TODO: Draw game info text.
			break;
		default:
			break;
		}
	}

	GameState Update(float dt, GameState gameState) {

		switch (gameState)
		{
		case GameState::MainMenu:
			if (m_leftMouseClicked) {
				// TODO: Update buttons.
			}
			break;
		case GameState::HelpMenu:
			if (m_leftMouseClicked) {
				// TODO: Update buttons.
			}
			if (m_escapePressed) {
				return GameState::MainMenu;
			}
			break;
		case GameState::DeathScreen:
			if (m_leftMouseClicked) {
				// TODO: Update buttons.
			}			
			if (m_escapePressed) {
				return GameState::MainMenu;
			}
			break;
		default:
			break;
		}


		m_escapePressed = false;
		m_leftMouseClicked = false;

		return GameState::MainMenu;
	}

};

