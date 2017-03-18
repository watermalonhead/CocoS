#pragma once
#include "ximacfg.h"

struct PointF
{
public:
	PointF();
	~PointF();
	float x;
	float y;
	float angle;
	float GetDistance(PointF & s);
	// 计算本点到d的角度
	float GetAngle(PointF & d);
};

