#include "PointF.h"
#include <math.h>

const float PI = 3.1415926f;

PointF::PointF()
{
	x = 0.0f;
	y = 0.0f;
	angle = 0.0f;
}


PointF::~PointF()
{
}


float PointF::GetDistance(PointF & s)
{
	return sqrt((x-s.x)*(x-s.x) + (y-s.y)*(y-s.y));
}


// 计算本点到d的角度
float PointF::GetAngle(PointF & d)
{
	// if (d.x - x == 0)
	if (fabs(d.x - x) < 1e-6)  // d.x == x
	{
		if (d.y - y < 0)
			return 270;
		else
			return 90;
	}
	float a = atan((d.y - y) / (d.x - x)) / PI * 180;
	if (d.x - x < 0)
		a += 180;
	return a;
}
