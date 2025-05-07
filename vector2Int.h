#pragma once
#include <iostream>

class Vector2Int {
private:
	int m_x;
	int m_y;

public:
	static Vector2Int zero;

	Vector2Int()
		: m_x{ 0 }
		, m_y{ 0 }
	{}

	Vector2Int(int x, int y)
		: m_x{ x }
		, m_y{ y }
	{}

	int x() const { return m_x; }
	void SetX(int x) { m_x = x; }
	int y() const { return m_y; }
	void SetY(int y) { m_y = y; }

	Vector2Int operator+=(const Vector2Int other) {
		m_x += other.m_x;
		m_y += other.m_y;
	}

};

inline Vector2Int Vector2Int::zero{ 0,0 };

inline Vector2Int operator+(const Vector2Int vector1, const Vector2Int vector2) {
	return { vector1.x() + vector2.x(),  vector1.y() + vector2.y() };
}

inline bool operator!=(const Vector2Int vector1, const Vector2Int vector2) {
	return  vector1.x() != vector2.x() || vector1.y() != vector2.y();
}

inline bool operator==(const Vector2Int vector1, const Vector2Int vector2) {
	return vector1.x() == vector2.x() && vector1.y() == vector2.y();
}

inline std::ostream& operator<< (std::ostream& stream, const Vector2Int& vector) {
	stream << "\"(" << vector.x() << ", " << vector.y() << ")\"";
	return stream;
}
