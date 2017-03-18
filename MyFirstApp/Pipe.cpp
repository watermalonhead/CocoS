#include "Pipe.h"


Pipe::Pipe(float x, float y, float vx, float vy) :cRole(x, y, vx, vy)
{
	SetImg(cImgManager::CreateImg(L"ËØ²Ä°ü\\ob5.png", CXIMAGE_FORMAT_PNG));
}


Pipe::~Pipe()
{
}

void Pipe::Update(float deltaTime)
{
	mPos.x -= xSpeed*deltaTime;
}
void  Pipe::Draw(HDC hdc)
{
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
}