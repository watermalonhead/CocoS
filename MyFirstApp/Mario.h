#pragma once
#include "cRole.h"
#include"PointF.h"
#include "sound\\Soundmanage.h"
class Mario :
	public cRole
{
public:
	static CSoundManage sound;
	Mario(float x, float y, float vx, float vy);
	~Mario();
	void Update(float deltaTime);
	void  Draw(HDC hdc);
	void ChangeSpeed(float Speed);
	void ChangeHigh(float Hight);
	void ChangeUp();
	void ChangeCurrentUp();
	void HeroHurt();
	void CoinAdd();
	float GetCoinCount();
protected:
	TCHAR filename[20];
	int Right = 1; //控制右动画
	int RUp = 5;	//控制上跳
	float FrameCount = 0;
	float Gravity = 9.8;
	bool lastKeyUp = false;
	bool CurrentUp = false;
	float GraMult = 70;
	float CoinCount = 0;
};

