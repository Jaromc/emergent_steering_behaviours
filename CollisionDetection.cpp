#include "CollisionDetection.h"

CollisionResult lineSegmentLineSegment(const Vector2f &p1,
                                       const Vector2f &p2,
                                       const Vector2f &p3,
                                       const Vector2f &p4)
{
	CollisionResult colRes;

	float denom = ((p4.y - p3.y) * (p2.x - p1.x)) - 
				   ((p4.x - p3.x) * (p2.y - p1.y));

	float enumA = ((p4.x - p3.x)*(p1.y - p3.y)) -
				((p4.y - p3.y)*(p1.x-p3.x));

	float enumB = ((p2.x - p1.x)*(p1.y - p3.y))-
				((p2.y - p1.y)*(p1.x - p3.x));

	if(denom == 0.f)
	{
		//the line segments are either coincident or parallel
		colRes.collision = false;
		return colRes;
	}

	float ua = enumA / denom;
	float ub = enumB / denom;

	//check for a collision between the intervals 0 - 1
	if (ua >= 0.f && ua <= 1.f && ub >= 0.f && ub <= 1.f)
	{
		//an intersection has occured
		colRes.collision = true;

		//get the contact points
		colRes.contactPoint.x = p1.x + (ua*(p2.x - p1.x));
		colRes.contactPoint.y = p1.y + (ub*(p2.y - p1.y));

		//get the contact normal
		Vector2f normal = p2 - p1;		
		colRes.contactNormal.x = -normal.y;
		colRes.contactNormal.y = normal.x;
		colRes.contactNormal = colRes.contactNormal.getNormalise();

		//get the depth
		colRes.depth = (p4 - colRes.contactPoint).length();

		return colRes;
	}

	//line segments are not itnersecting
	colRes.collision = false;
	return colRes;
}