#pragma once
#include "PointF.h"
#include "cImg.h"
#include "cImgManager.h"

class IMovable
{
public:
	IMovable(float x, float y, float vx, float vy);
	~IMovable();
protected:
	PointF mPos;
	float xSpeed;
	float ySpeed;
	cImg* mImg;
	float mWidth;
	float mHeight;
public:
	virtual void Update(float deltaTime);
	virtual void Draw(HDC hdc);
	PointF GetPos();
	RECT GetRect();
	void SetImg(cImg* img);
	float GetSpeed();
	float GetHeight();
};

