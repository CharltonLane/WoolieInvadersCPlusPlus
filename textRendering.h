#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include "vector2.h"
#include "spaceConversion.h"

namespace TextRendering {

	constexpr SDL_Color g_colorBlack{ 0, 0, 0, 255 };
	constexpr SDL_Color g_colorWhite{ 255, 255, 255, 255 };
	constexpr SDL_Color g_colorYellow{ 255, 195, 67, 255 };

	inline static SDL_Color g_textColor{ g_colorWhite };

	inline static void SetTextColor(SDL_Color color) {
		g_textColor = color;
	}

	inline static void DrawTextAt(SDL_Renderer* renderer, std::string text, Vector2 position, bool useUnderlay = true) {
		// Top-left aligned text relative to position.
		if (useUnderlay) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 127);
			SDL_RenderDebugText(renderer, position.x() + 1, position.y() + 1, text.c_str());
		}

		SDL_SetRenderDrawColor(renderer, g_textColor.r, g_textColor.g, g_textColor.b, SDL_ALPHA_OPAQUE);
		SDL_RenderDebugText(renderer, position.x(), position.y(), text.c_str());
	}

	inline static void DrawTextAt(SDL_Renderer* renderer, int integerValue, Vector2 position, bool useUnderlay = true) {
		std::string string = std::to_string(static_cast<int>(integerValue));
		DrawTextAt(renderer, string, position, useUnderlay);
	}

	inline static void DrawCenteredText(SDL_Renderer* renderer, std::string text) {
		float x, y;

		/* Center the message and scale it up */
		x = (SpaceConversion::g_gamePixelWidth / 2 - (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(text.c_str()) / 2));
		y = (SpaceConversion::g_gamePixelHeight / 2 - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE / 2);

		DrawTextAt(renderer, text, { x,y });
	}
}