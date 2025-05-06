#pragma once
#include "vector2.h"

namespace SpaceConversion {

	// For simplicity, world space units are defined as every grid cell. 
	
	// World space: How objects are placed in the world. Arbitrary unit system. Logically, defining one grid cell as a world unit.
	// Pixel space: space in relation to the displayed pixels of the pixel art. This isn't always 1:1 with pixels on the monitor.
	//				This is 8 pixel art pixels to one world unit.
	// Screen space: Pixels on the monitor.
	//				 This is 4 monitor pixels to one pixel art pixel. (Set via SDL_SetRenderScale in main.cpp)

	constexpr float g_gamePixelWidth{ 200 };
	constexpr float g_gamePixelHeight{ 150 };
	constexpr float g_pixelsPerUnit{ 8 };

	constexpr float g_screenPixelsPerPixelArtPixel{ 4.0f };

	inline Vector2 WorldToPixel(const Vector2& worldSpace) {
		return { worldSpace * g_pixelsPerUnit };
	}

	inline Vector2 PixelToWorld(const Vector2& pixelSpace) {
		return { pixelSpace / g_pixelsPerUnit };
	}
	
	inline Vector2 ScreenToPixel(const Vector2& screenSpace) {
		return { screenSpace / g_screenPixelsPerPixelArtPixel };
	}
}