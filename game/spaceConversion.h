#pragma once
#include "vector2.h"

namespace SpaceConversion {

	// For simplicity, world space units are defined as every grid cell. 
	
	// Camera space: Objects drawn relative to the game's camera.
	//				Sprites can be made to draw in this space via a bool in their Render();
	// 
	// World space: How objects are placed in the world. Arbitrary unit system. Logically, defining one grid cell as a world unit.
	// Pixel space: space in relation to the displayed pixels of the pixel art. This isn't always 1:1 with pixels on the monitor.
	//				This is 8 pixel art pixels to one world unit.
	// Screen space: Pixels on the monitor.
	//				 This is 4 monitor pixels to one pixel art pixel. (Set via SDL_SetRenderScale in main.cpp)

	// TODO: Make this relative to the window size, so the game is still positioned correctly on non-16:9 window sizes.
	inline Vector2 g_cameraPosition{ -60,-20 };

	constexpr int g_windowWidth{ 1280 };
	constexpr int g_windowHeight{ 720 };

	constexpr float g_gamePixelWidth{ 320 };
	constexpr float g_gamePixelHeight{ 180 };
	constexpr float g_pixelsPerUnit{ 8 };

	// Is changed when entering fullscreen to suit the monitor's resolution.
	// The default value here of 4 matches the default g_windowWidth/Height and g_gamePixelWidth/Height.
	inline float g_pixelArtScale{ 4.0f }; 

	inline Vector2 WorldToPixel(const Vector2& worldSpace) {
		return { worldSpace * g_pixelsPerUnit };
	}

	inline Vector2 PixelToWorld(const Vector2& pixelSpace) {
		return { pixelSpace / g_pixelsPerUnit };
	}
	
	inline Vector2 ScreenToPixel(const Vector2& screenSpace) {
		return { screenSpace / g_pixelArtScale };
	}
}