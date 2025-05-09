#pragma once
#include <iostream>
#include "vector2Int.h"


class Vector2 {
private:
	float m_x;
	float m_y;

public:
	Vector2()
		: m_x{ 0 }
		, m_y{ 0 }
	{}

	Vector2(float x, float y)
		: m_x{ x }
		, m_y{ y }
	{}

	Vector2(Vector2Int intVector)
		: m_x{ static_cast<float>(intVector.x()) }
		, m_y{ static_cast<float>(intVector.y()) }
	{}

	float x() const { return m_x; }
	void SetX(float x) { m_x = x; }
	float y() const { return m_y; }
	void SetY(float y) { m_y = y; }


	Vector2 operator+=(const Vector2 other) {
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}
};

inline Vector2 operator*(const Vector2 vector, const float scalar) {
	return Vector2{ vector.x() * scalar, vector.y() * scalar };
}
inline Vector2 operator*(const float scalar, const Vector2 vector) {
	return vector * scalar;
}


inline Vector2 operator/(const Vector2 vector, const float scalar) {
	return Vector2{ vector.x() / scalar, vector.y() / scalar };
}
inline Vector2 operator/(const float scalar, const Vector2 vector) {
	return vector / scalar;
}

inline Vector2 operator+(const Vector2 vector1, const Vector2Int vector2) {
	return { vector1.x() + vector2.x(), vector1.y() * vector2.y() };
}

inline std::ostream& operator<< (std::ostream& stream, const Vector2& vector) {
	stream << "\"(" << vector.x() << ", " << vector.y() << ")\"";
	return stream;
}
