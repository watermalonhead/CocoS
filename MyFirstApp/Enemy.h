#pragma once
#include "cRole.h"
class Enemy :
	public cRole
{
public:
	Enemy(float x, float y, float vx, float vy);
	~Enemy();
	void Update(float deltaTime);
	void  Draw(HDC hdc);
	bool isCollision = false;
protected:
	TCHAR filename[20];
	int PicControl = 1;
	float FrameCount = 0;
};

