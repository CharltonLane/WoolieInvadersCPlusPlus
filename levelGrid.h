#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "vector2.h"

class LevelGrid
{
	// Represents the game's world.
	// Can provide info about solid/unwalkable tiles.

private:
	// TODO: Could load this in from a b/w image. Or even just a string with X and _ for solid or not.
	const std::vector<int> m_solidTileIndices
	{     0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
		 25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
		 50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,                                               71,  72,  73,  74,
		 75,                                                                   89,  90,  91,  92,  93,  94,                 98,  99,
		100,                                                                                                                    124,
		125,                                                                                                                    149,
		150,                                              160,           163,           166,           169,      171,           174,
		175,                                              185,           188,           191,           194,      196,           199,
		200,           203, 204,      206, 207,           210,           213,           216,           219,      221,           224,
		225,                                              235,           238,           241,                                    249,
		250,                                              260,           263,           266,           269,      271,           274,
		275,           278, 279,      281, 282,           285,           288,           291,           294,      296,           299,
		300,                                              310,           313,           316,           319,      321,           324,
		325,                                              335,           338,                                                   349,
		350,           353, 354,      356, 357,                                                                                 374,
		375,                                                                                                                    399,
		400,                                                                                                                    424,
		425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449
	};

	const std::vector<int> m_spawnpointIndices{ 69, 103, 121, 192, 220, 255, 265, 337, 371, 378, 390 };

	const int m_levelWidth{ 25 };
	const int m_levelHeight{ 19 };

	std::vector<Vector2Int> m_solidTiles{};
	std::vector<Vector2Int> m_spawnPointTiles{};

	constexpr void SetupTileVectors() {
		// Transform our index arrays into a list of Vector2Int containing each tile's world space position.
		m_solidTiles = std::vector<Vector2Int>(m_solidTileIndices.size());
		m_spawnPointTiles = std::vector<Vector2Int>(m_spawnpointIndices.size());

		for (int index{ 0 }; index < std::ssize(m_solidTileIndices); index++)
		{
			std::size_t unsignedIndex = static_cast<std::size_t>(index);
			int value = m_solidTileIndices[unsignedIndex];
			int x = (value % m_levelWidth);
			int y = value / m_levelWidth; // intentional int division.
			m_solidTiles[unsignedIndex] = Vector2Int{ x, y };
		}

		for (int index{ 0 }; index < std::ssize(m_spawnpointIndices); index++)
		{
			std::size_t unsignedIndex = static_cast<std::size_t>(index);
			int value = m_spawnpointIndices[unsignedIndex];
			int x = (value % m_levelWidth);
			int y = value / m_levelWidth; // intentional int division.
			m_spawnPointTiles[unsignedIndex] = Vector2Int{ x, y };
		}
	}

public:
	constexpr LevelGrid()
	{
		SetupTileVectors();
	}

	~LevelGrid()
	{
	}

	bool IsTileSolid(const Vector2Int& worldPosition);

	const std::vector<Vector2Int> GetRandomSpawnPoints(int count);
};

