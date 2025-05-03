#pragma once

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
		return { m_x + other.m_x, m_y + other.m_y };
	}

	bool operator!=(const Vector2Int other) {
		return m_x != other.m_x || m_y != other.m_y;
	}

	Vector2Int operator+(const Vector2Int other) {
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}

};
inline Vector2Int Vector2Int::zero{ 0,0 };

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

	Vector2 operator*(const float scalar) const {
		return Vector2{ m_x * scalar, m_y * scalar };
	}

	Vector2 operator/(const float scalar) const {
		return Vector2{ m_x / scalar, m_y / scalar };
	}

	Vector2 operator+=(const Vector2 other) {
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}

	Vector2 operator+(const Vector2Int other) {
		m_x += other.x();
		m_y += other.y();
		return *this;
	}
};


