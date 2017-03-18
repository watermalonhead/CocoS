#include "Brick.h"


Brick::Brick(float x, float y, float vx, float vy) :cRole(x, y, vx, vy)
{
	SetImg(cImgManager::CreateImg(L"ËØ²Ä°ü\\ob1.png", CXIMAGE_FORMAT_PNG));
}


Brick::~Brick()
{
}
void Brick::Update(float deltaTime)
{
	mPos.x -= xSpeed*deltaTime;
}
void  Brick::Draw(HDC hdc)
{
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
}