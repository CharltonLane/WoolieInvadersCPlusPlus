#define SDL_MAIN_USE_CALLBACKS 1  // Use the callbacks instead of main().
#include <string>
#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_image/SDL_image.h>

#include "game.h"
#include "menu.h"
#include "appState.h"
#include "spaceConversion.h"
#include "textRendering.h"

constexpr SDL_AudioSpec g_audioSpec{ MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_DEFAULT_FREQUENCY };
bool g_fullscreen{ false };

// This function runs once at startup.
// See https://wiki.libsdl.org/SDL3/README-main-functions
SDL_AppResult SDL_AppInit(void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	*appstate = new AppState{};
	AppState& state = *static_cast<AppState*>(*appstate);

	// Init audio.
	if (!SDL_Init(SDL_INIT_AUDIO)) {
		printf("SDL_INIT_AUDIO could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
	}
	if (!Mix_OpenAudio(0, &g_audioSpec))
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
	}

	// Create the window in windowed mode using a preset resolution.
	if (!SDL_CreateWindowAndRenderer("WoolieInvaders (C++ Edition!)", SpaceConversion::g_windowWidth, SpaceConversion::g_windowHeight, 0, &state.window, &state.renderer)) {
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// Turn vsync on since the game doesn't need to run at thousands of fps.
	SDL_SetRenderVSync(state.renderer, 1);

	state.menu = std::move(std::make_unique<Menu>(state.renderer));
	state.game = std::move(std::make_unique<Game>(state.renderer));

	return SDL_APP_CONTINUE;
}

// This function runs when a new event (mouse input, keypresses, etc) occurs.
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	AppState& state = *static_cast<AppState*>(appstate);

	// Game exit inputs.
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
	}

	else if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_F11) {
		// Toggle fullscreen.
		g_fullscreen = !g_fullscreen;

		SDL_SetWindowFullscreen(state.window, g_fullscreen);
		SDL_SyncWindow(state.window);

		int w{ 0 };
		int h{ 0 };
		if (SDL_GetCurrentRenderOutputSize(state.renderer, &w, &h)) {
			SpaceConversion::g_pixelArtScale = h / SpaceConversion::g_gamePixelHeight;
		}
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
		state.menu->HandleInput(event);
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

// Variables to calculate delta time.
static Uint64 NOW = SDL_GetPerformanceCounter();
static Uint64 LAST = 0;
static float deltaTime = 0;

// FPS counter.
static float fpsCounterSmoothValue{ 0 };
static float fpsCounterAverageSum{ 0 };
static int fpsCounterAverageFrameCounter{ 0 };
// Refresh FPS every tenth of a second.
constexpr float fpsCounterRefreshAfterSeconds{ 0.1f };


/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void* appstate)
{
	AppState& state = *static_cast<AppState*>(appstate);

	// Delta Time.
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (float)((NOW - LAST) / (float)SDL_GetPerformanceFrequency());

	// FPS counter.
	fpsCounterAverageSum += deltaTime;
	fpsCounterAverageFrameCounter++;
	if (fpsCounterAverageSum >= fpsCounterRefreshAfterSeconds) {
		fpsCounterSmoothValue = fpsCounterAverageSum / fpsCounterAverageFrameCounter;
		fpsCounterAverageSum = 0;
		fpsCounterAverageFrameCounter = 0;
	}

	const float scale = SpaceConversion::g_pixelArtScale;
	SDL_SetRenderScale(state.renderer, scale, scale);

	// Draw the background color.
	SDL_SetRenderDrawColor(state.renderer, 52, 9, 12, 255); // Red background.
	SDL_RenderClear(state.renderer);
	SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);

	GameState updatedGameState{ state.gameState };

	switch (state.gameState)
	{
	case GameState::MainMenu:
	case GameState::HelpMenu:
	case GameState::DeathScreen:
		updatedGameState = state.menu->Update(state.gameState);
		state.menu->Render(state.renderer, state);
		//SDL_RenderDebugText(state.renderer, x, ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE), std::to_string(static_cast<int>(1 / deltaTime)).c_str());

		if (updatedGameState == GameState::Ingame) {
			state.game->StartGame();
		}

		break;
	case GameState::Ingame:
		updatedGameState = state.game->Update(deltaTime);
		state.game->Render(state.renderer);

		if (updatedGameState != GameState::Ingame) {
			state.game->EndGame();
			state.menu->Render(state.renderer, state);
		}

		break;
	default:
		break;
	}

	// Draw fps
	const std::string fpsString = std::to_string(static_cast<int>(1 / fpsCounterSmoothValue));
	float fpsWidth = static_cast<float>(SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(fpsString.c_str()));
	TextRendering::DrawTextAt(state.renderer, fpsString, { SpaceConversion::g_gamePixelWidth - fpsWidth, 0 });

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

