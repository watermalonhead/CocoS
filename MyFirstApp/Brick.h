#pragma once
#include "cRole.h"
class Brick :
	public cRole
{
public:
	Brick(float x, float y, float vx, float vy);
	~Brick();
	void Update(float deltaTime);
	void  Draw(HDC hdc);
};

