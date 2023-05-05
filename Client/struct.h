#pragma once

// ũ��� ������ ��Ÿ���� ���� �ڷ��� ����
struct Vec2
{
	float x;
	float y;

private:
	float length()
	{
		return sqrt(x * x + y * y);
	}

public:

	Vec2& normalize()
	{
		float fLen = length();
		
		assert(fLen != 0.f);	// ���� �����̸� Stop!

		x /= fLen;
		y /= fLen;

		return *this;
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
};