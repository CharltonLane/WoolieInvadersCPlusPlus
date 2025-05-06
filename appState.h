#pragma once
#include <SDL3/SDL.h>


enum class GameState {
	MainMenu,
	HelpMenu,
	Ingame,
	DeathScreen
};

class Menu;
class Game;

struct AppState {

	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	Menu* menu{ nullptr };
	Game* game{ nullptr };
	GameState gameState{ GameState::MainMenu };
};