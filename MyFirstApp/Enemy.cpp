#include "Enemy.h"

Enemy::Enemy(float x, float y, float vx, float vy) :cRole(x, y, vx, vy)
{
	_stprintf(filename, L"ËØ²Ä°ü\\flower%d.png", PicControl);
	SetImg(cImgManager::CreateImg(filename, CXIMAGE_FORMAT_PNG));
}
Enemy::~Enemy()
{

}

void Enemy::Update(float deltaTime)
{
	mPos.x -= xSpeed*deltaTime;
	#pragma region picture select

	if (FrameCount>0.1f)
	{
		FrameCount = FrameCount - 0.1;
	}
	FrameCount += deltaTime;
	if (FrameCount>0.1f)
	{
		PicControl++;
		if (PicControl>2)
		{
			PicControl = 1;
		}
		_stprintf(filename, L"ËØ²Ä°ü\\flower%d.png", PicControl);
	}

#pragma endregion

}
void Enemy::Draw(HDC hdc)
{
	SetImg(cImgManager::CreateImg(filename, CXIMAGE_FORMAT_PNG));
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
}
