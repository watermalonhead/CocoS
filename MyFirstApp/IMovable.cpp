#include "IMovable.h"


IMovable::IMovable(float x, float y, float vx, float vy)
{
	xSpeed = vx;
	ySpeed = vy;
	mWidth = 0.0f;
	mHeight = 0.0f;
	mPos.x = x;
	mPos.y = y;
	mPos.angle = 0;
	mImg = NULL;
}
float IMovable::GetSpeed()
{
	return xSpeed;
}

IMovable::~IMovable()
{
}


void IMovable::Update(float deltaTime)
{
	mPos.x += xSpeed * deltaTime;
	mPos.y += ySpeed * deltaTime;
}


void IMovable::Draw(HDC hdc)
{
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
}


PointF IMovable::GetPos()
{
	return mPos;
}


RECT IMovable::GetRect()
{
	RECT r;
	r.left = mPos.x - mWidth / 2;
	r.top = mPos.y - mHeight / 2;
	r.right= mPos.x + mWidth / 2;
	r.bottom = mPos.y + mHeight / 2;
	return r;
}


void IMovable::SetImg(cImg* img)
{
	mImg = img;
	mWidth = img->GetWidth();
	mHeight = img->GetHeight();
}

float IMovable::GetHeight()
{
	return mWidth;
}