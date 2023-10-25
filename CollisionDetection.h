#pragma once

#include "Vector2.h"

struct CollisionResult
{
	Vector2f contactPoint;
	Vector2f contactNormal;
	bool collision;
	float depth;
};

CollisionResult lineSegmentLineSegment(const Vector2f &p1,
											const Vector2f &p2,
											const Vector2f &p3,
											const Vector2f &p4);
