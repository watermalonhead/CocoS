#pragma once
#include "IMovable.h"
class cCloud :
	public IMovable
{
public:
	cCloud(float x, float y, float vx, float vy);
	~cCloud();
};

