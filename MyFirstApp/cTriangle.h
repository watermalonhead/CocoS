#pragma once
#include "cRole.h"
class cTriangle :
	public cRole
{
public:
	cTriangle(float x, float y, float vx, float vy);
	~cTriangle();
	void Update(float deltaTime);
	void  Draw(HDC hdc);
	void LifeHurt();
	void Death();
	float timer;
	bool isCollision = false;
	void ChangeSpeed(float Speed);
protected:
	TCHAR filename[20];
	int PicControl = 1;
	float FrameCount = 0;
	bool death;
};

