#pragma once
#include "cRole.h"
class Turtle :
	public cRole
{
public:
	Turtle(float x, float y, float vx, float vy);
	~Turtle();
	void Update(float deltaTime);
	void  Draw(HDC hdc);
	void LifeHurt();
	void Death();
	float timer;
	bool isCollision = false;
	void ChangeSpeed(float Speed)
	{
		xSpeed = Speed;
	}
protected:
	TCHAR filename[20];
	int PicControl = 1;
	float FrameCount = 0;
	bool death;
};

