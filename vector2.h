#pragma once

class Vector2Int {
private:
	int m_x;
	int m_y;

public:
	Vector2Int()
		: m_x{ 0 }
		, m_y{ 0 }
	{}

	Vector2Int(int x, int y)
		: m_x{ x }
		, m_y{ y }
	{}

	int x() const { return m_x; }
	int y() const { return m_y; }
};

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
	float y() const { return m_y; }
};


