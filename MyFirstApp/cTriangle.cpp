#include "cTriangle.h"
#include"cApp.h"

cTriangle::cTriangle(float x, float y, float vx, float vy) :cRole(x, y, vx, vy)
{
	_stprintf(filename, L"ËØ²Ä°ü\\triangle%d.png", PicControl);
	SetImg(cImgManager::CreateImg(filename, CXIMAGE_FORMAT_PNG));
	timer = 0;
	death = false;
}
void cTriangle::ChangeSpeed(float Speed)
{
	xSpeed = Speed;
}
void cTriangle::LifeHurt()
{
	mLife--;
}
cTriangle::~cTriangle()
{
}

void cTriangle::Update(float deltaTime)
{
	if (death)
	{
		timer += deltaTime;
		if (timer > 0.5)
		{
			cApp::mManager.Erase(this);
			delete(this);
			return;
		}
		
	}
	mPos.x -= xSpeed*deltaTime;
#pragma region picture select

	if (FrameCount>0.1f)
	{
		FrameCount = FrameCount - 0.1;
	}
	FrameCount += deltaTime;
	if (FrameCount>0.1f&&mLife>0)
	{
		PicControl++;
		if (PicControl>2 && mLife>0)
		{
			PicControl = 1;
		}
		_stprintf(filename, L"ËØ²Ä°ü\\triangle%d.png", PicControl);
		SetImg(cImgManager::CreateImg(filename, CXIMAGE_FORMAT_PNG));
	}
}
void cTriangle::Draw(HDC hdc)
{
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
}

void cTriangle::Death()
{
	death = true;
}