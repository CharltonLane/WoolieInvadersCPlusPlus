/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>
#include "sprite.h"
#include "gridEntity.h"
#include "game.h"
#include "menu.h"
#include "appState.h"
#include "spaceConversion.h"



/* This function runs once at startup. */
// https://wiki.libsdl.org/SDL3/README/main-functions
SDL_AppResult SDL_AppInit(void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	*appstate = new AppState;
	AppState& state = *static_cast<AppState*>(*appstate);

	/* Create the window */
	// Use SDL_WINDOW_FULLSCREEN for fullscreen.
	if (!SDL_CreateWindowAndRenderer("Woolie Invaders (C++ Edition!)", 800, 600, 0, &state.window, &state.renderer)) {
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	state.menu = new Menu{ state.renderer };
	state.game = new Game{ state.renderer };

	return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	AppState& state = *static_cast<AppState*>(appstate);

	// Game exit inputs.
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}

	if (state.gameState == GameState::MainMenu) {
		if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
			return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
		}
	}

	// Standard game inputs.
	switch (state.gameState)
	{
	case GameState::MainMenu:
	case GameState::HelpMenu:
	case GameState::DeathScreen:
		state.menu->HandleInput(event, state.gameState);
		break;
	case GameState::Ingame:
		//std::cout << event->type << "\n";
		if (event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
			state.game->HandleInput(event);
		}
		break;
	default:
		break;
	}


	return SDL_APP_CONTINUE;
}


static Uint64 NOW = SDL_GetPerformanceCounter();
static Uint64 LAST = 0;
static float deltaTime = 0;

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
	AppState& state = *static_cast<AppState*>(appstate);

	// Delta Time.
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();

	deltaTime = (float)((NOW - LAST) / (float)SDL_GetPerformanceFrequency());
	//std::cout << "FPS: " << 1/deltaTime << "\n";

	const char* message = "Hello World!";
	int w = 0, h = 0;
	float x, y;
	const float scale = SpaceConversion::g_screenPixelsPerPixelArtPixel;

	/* Center the message and scale it up */
	SDL_GetRenderOutputSize(state.renderer, &w, &h);
	SDL_SetRenderScale(state.renderer, scale, scale);
	x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
	y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

	/* Draw the message */
	SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
	SDL_RenderClear(state.renderer);
	SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
	//SDL_RenderDebugText(state.renderer, x, y, message);

	GameState updatedGameState{ state.gameState };

	switch (state.gameState)
	{
	case GameState::MainMenu:
	case GameState::HelpMenu:
	case GameState::DeathScreen:
		updatedGameState = state.menu->Update(deltaTime, state.gameState);
		state.menu->Render(state.renderer, state.gameState);
		SDL_RenderDebugText(state.renderer, x, ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), std::to_string(static_cast<int>(1 / deltaTime)).c_str());

		break;
	case GameState::Ingame:
		updatedGameState = state.game->Update(deltaTime);
		state.game->Render(state.renderer);
		break;
	default:
		break;
	}


	SDL_RenderDebugText(state.renderer, x, ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), std::to_string(static_cast<int>(1 / deltaTime)).c_str());


	SDL_RenderPresent(state.renderer);

	state.gameState = updatedGameState;
	if (updatedGameState == GameState::Quit) {
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}
	return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit([[maybe_unused]] void* appstate, [[maybe_unused]] SDL_AppResult result)
{
}

