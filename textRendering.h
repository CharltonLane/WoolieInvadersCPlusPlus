#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include "spaceConversion.h"

namespace TextRendering {
	static void DrawCenteredText(SDL_Renderer* renderer, std::string text) {
		float x, y;

		/* Center the message and scale it up */
		x = (SpaceConversion::g_gamePixelWidth / 2 - (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(text.c_str()) / 2));
		y = (SpaceConversion::g_gamePixelHeight / 2 - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE / 2);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 127);
		SDL_RenderDebugText(renderer, x + 1, y + 1, text.c_str());

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDebugText(renderer, x, y, text.c_str());

	}
}