#pragma once




struct Vec2
{
	float x;
	float y;
public:
	Vec2()
		:x(0.0f),y(0.0f)
	{}

	Vec2(const float& fx, const float& fy)
		:x(fx),y(fy)
	{}

	Vec2(const int& fx, const int& fy)
		:x(static_cast<int>(fx)),y(static_cast<int>(fy))
	{}
};