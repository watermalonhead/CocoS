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
	// ���㱾�㵽d�ĽǶ�
	float GetAngle(PointF & d);
};

