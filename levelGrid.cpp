#include "levelGrid.h"

bool LevelGrid::IsTileSolid(Vector2Int worldPosition) {
	bool solid{ std::count(m_solidTiles.begin(), m_solidTiles.end(), worldPosition) > 0 };
	//if (solid) {
	//	std::cout << worldPosition.x() << ", " << worldPosition.y() << " is solid\n";
	//}
	//else {
	//	std::cout << worldPosition.x() << ", " << worldPosition.y() << " is walkable\n";
	//}
	return solid;
}
