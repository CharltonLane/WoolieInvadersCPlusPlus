#pragma once
#include <memory>
#include <SDL3/SDL.h>


enum class GameState {
	MainMenu,
	HelpMenu,
	Ingame,
	DeathScreen,
	Quit
};

class Menu;
class Game;

struct AppState {

	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	std::unique_ptr<Menu> menu{};
	std::unique_ptr<Game> game{};
	GameState gameState{ GameState::MainMenu };
};