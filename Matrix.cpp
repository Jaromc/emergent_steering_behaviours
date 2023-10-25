#include "Matrix.h"
#include <cstring>

Matrix2::Matrix2()
{
	memset(data, 0, sizeof(data)); 
}

void Matrix2::setTransform(const Vector2f& pos, float rot)
{
	setRotation(rot);
	setTranslation(pos);
}

void Matrix2::setRotation(float radians)
{	
	data[0][0] = cos(radians); 
	data[0][1] = sin(radians);
	data[1][0] = -sin(radians);
	data[1][1] = cos(radians);
}

void Matrix2::setTranslation(const Vector2f &translation)
{
	data[2][0] = translation.x;
	data[2][1] = translation.y;
}

Vector2f Matrix2::transform(const Vector2f &v)
{
	Vector2f res;

	res.x = ((v.x * data[0][0]) + (v.y * data[1][0])) + data[2][0];
	res.y = ((v.x * data[0][1]) + (v.y * data[1][1])) + data[2][1];

	return res;
}