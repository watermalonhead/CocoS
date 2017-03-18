#include "Mario.h"
#include"cApp.h"
#define Jump 1
CSoundManage Mario::sound;
Mario::Mario(float x, float y, float vx, float vy) :cRole(x, y, vx, vy)
{
	//_stprintf(filename, L"ËØ²Ä°ü\\%d.png", 1);
	SetImg(cImgManager::CreateImg(L"ËØ²Ä°ü\\1.png", CXIMAGE_FORMAT_PNG));
	mLife = 5;
}
float Mario::GetCoinCount()
{
	return CoinCount;
}
void Mario::CoinAdd()
{
	CoinCount++;
}
void Mario::ChangeUp()
{
	lastKeyUp = false;
}
void Mario::ChangeSpeed(float Speed)
{
	xSpeed = Speed;
}
void Mario::ChangeHigh(float Hight)
{
	mPos.y = Hight;
}
void Mario::ChangeCurrentUp()
{
	CurrentUp = true;
}
Mario::~Mario()
{
}
void Mario::HeroHurt()
{
	mLife--;
}
void Mario::Update(float deltaTime)
{

	if (FrameCount > 0.1f)
	{
		FrameCount = FrameCount - 0.1;
	}
	FrameCount += deltaTime;
	if (CurrentUp&&!lastKeyUp)
	{
		lastKeyUp = CurrentUp; //Jump
		ySpeed = -300;
	}
	CurrentUp = cApp::IsKeyDown(VK_UP);
	if (cApp::IsKeyDown(VK_UP) && !lastKeyUp)
	{
		sound.ReadFile(Jump, "ËØ²Ä°ü\\Sound\\Ìø.mp3", DOSOUND);
		sound.play(Jump);
	}
	mPos.x -= xSpeed*deltaTime;
	mPos.y += ySpeed * deltaTime;
	ySpeed += Gravity*deltaTime*GraMult;
#pragma region position

	if (mPos.y > 385)
	{
		mPos.y = 385;
		lastKeyUp = false;
	}
#pragma endregion

#pragma region picture select

	if (cApp::IsKeyDown(VK_UP) && FrameCount > 0.1f&&mLife > 0)
	{
		_stprintf(filename, L"ËØ²Ä°ü\\%d.png", RUp);
		SetImg(cImgManager::CreateImg(filename, CXIMAGE_FORMAT_PNG));
	}
	else if (FrameCount > 0.1f&&mLife > 0)
	{
		_stprintf(filename, L"ËØ²Ä°ü\\%d.png", Right);
		Right++;
		if (Right > 4)
		{
			Right = 1;
		}
		SetImg(cImgManager::CreateImg(filename, CXIMAGE_FORMAT_PNG));
	}

#pragma endregion

}

void Mario::Draw(HDC hdc)
{
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
}