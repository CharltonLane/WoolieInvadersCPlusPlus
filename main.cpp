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
#include "sprite.h"
#include "gridEntity.h"
#include "game.h"

struct AppState {
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	Sprite mySprite{};

	Game game{};
};


/* This function runs once at startup. */
// https://wiki.libsdl.org/SDL3/README/main-functions
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	*appstate = new AppState;
	AppState& state = *static_cast<AppState*>(*appstate);


	/* Create the window */
	// Use SDL_WINDOW_FULLSCREEN for fullscreen.
	if (!SDL_CreateWindowAndRenderer("Hello World", 800, 600, 0, &state.window, &state.renderer)) {
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// Create a cheeky sprite.
	state.mySprite = Sprite{ state.renderer, "images/test.png" };
	state.game = Game{ state.renderer };

	return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_KEY_DOWN ||
		event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}
	return SDL_APP_CONTINUE;
}


/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
	AppState& state = *static_cast<AppState*>(appstate);

	const char* message = "Hello World!";
	int w = 0, h = 0;
	float x, y;
	const float scale = 4.0f;

	/* Center the message and scale it up */
	SDL_GetRenderOutputSize(state.renderer, &w, &h);
	SDL_SetRenderScale(state.renderer, scale, scale);
	x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
	y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

	/* Draw the message */
	SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
	SDL_RenderClear(state.renderer);
	SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
	SDL_RenderDebugText(state.renderer, x, y, message);

	// Draw our super cool sprite.
	//state.mySprite.Render(state.renderer);
	state.game.Update();
	state.game.Render(state.renderer);

	SDL_RenderPresent(state.renderer);

	return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
}

