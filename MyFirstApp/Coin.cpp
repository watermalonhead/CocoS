#include "Coin.h"
#include"cApp.h"

Coin::Coin(float x, float y, float vx, float vy) :cRole(x, y, vx, vy)
{
	_stprintf(filename, L"ËØ²Ä°ü\\coin%d.png", PicControl);
	SetImg(cImgManager::CreateImg(filename, CXIMAGE_FORMAT_PNG));
	timer = 0;
	GetCoin = false;
}


Coin::~Coin()
{
}
bool Coin::isGet()
{
	return GetCoin;
}
void Coin::Update(float deltaTime)
{
	if (GetCoin)
	{
		timer += deltaTime;
		if (timer > 0.1f)
		{
			cApp::CoinManger.Erase(this);
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
	if (FrameCount>0.1f&&!GetCoin)
	{
		PicControl++;
		if (PicControl>2)
		{
			PicControl = 1;
		}
		_stprintf(filename, L"ËØ²Ä°ü\\coin%d.png", PicControl);
		SetImg(cImgManager::CreateImg(filename, CXIMAGE_FORMAT_PNG));
	}

}

void Coin::Draw(HDC hdc)
{
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
}

void Coin::Get()
{
	GetCoin = true;
}

