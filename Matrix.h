#pragma once

#include "Vector2.h"

class Matrix2
{
private:
	float data[3][3];
public:
	Matrix2();
	~Matrix2(){}
	void setTransform(const Vector2f& pos, float rot);
	void setRotation(float radians);
	void setTranslation(const Vector2f &translation);
	Vector2f transform(const Vector2f &v);
};


