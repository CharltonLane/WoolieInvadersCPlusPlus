#include "levelGrid.h"
#include "random.h"

bool LevelGrid::IsTileSolid(const Vector2Int& worldPosition) {
	bool solid{ std::count(m_solidTiles.begin(), m_solidTiles.end(), worldPosition) > 0 };
	//if (solid) {
	//	std::cout << worldPosition.x() << ", " << worldPosition.y() << " is solid\n";
	//}
	//else {
	//	std::cout << worldPosition.x() << ", " << worldPosition.y() << " is walkable\n";
	//}
	return solid;
}

 const std::vector<Vector2Int> LevelGrid::GetRandomSpawnPoints(int count) {

	if (count > m_spawnPointTiles.size()) {
		count = static_cast<int>(m_spawnPointTiles.size());
	}

	std::vector<Vector2Int> spawnPoints(count);

	std::mt19937 r = Random::generate();
	std::shuffle(m_spawnPointTiles.begin(), m_spawnPointTiles.end(), r);

	for (size_t i = 0; i < count; i++)
	{
		spawnPoints[i] = m_spawnPointTiles[i];
	}

	return spawnPoints;
}
