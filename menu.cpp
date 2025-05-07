#include "Menu.h"

void Menu::HandleInput(const SDL_Event* event) {

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
			//std::cout << "Click!" << "\n";
		}
	}
}

GameState Menu::Update([[maybe_unused]]float dt, GameState gameState) {

	GameState returnState{ gameState };

	switch (gameState)
	{
	case GameState::MainMenu:
		m_playGameButton.Update(m_mouseScreenPosition);
		m_helpButton.Update(m_mouseScreenPosition);
		m_quitGameButton.Update(m_mouseScreenPosition);
		if (m_leftMouseClicked) {
			if (m_playGameButton.IsWithinButton(m_mouseScreenPosition, true)) {
				std::cout << "START THE GAME!!!\n";
				returnState = GameState::Ingame;
			}
			if (m_helpButton.IsWithinButton(m_mouseScreenPosition, true)) {
				returnState = GameState::HelpMenu;
			}
			if (m_quitGameButton.IsWithinButton(m_mouseScreenPosition, true)) {
				returnState = GameState::Quit;
			}
		}
		break;
	case GameState::HelpMenu:
		m_playGameButton.Update(m_mouseScreenPosition);
		m_helpScreenDoneButton.Update(m_mouseScreenPosition);
		if (m_leftMouseClicked) {
			if (m_helpScreenDoneButton.IsWithinButton(m_mouseScreenPosition, true)) {
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
			if (m_deathScreenDoneButton.IsWithinButton(m_mouseScreenPosition, true)) {
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

void Menu::Render(SDL_Renderer* renderer, GameState gameState) const {
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
