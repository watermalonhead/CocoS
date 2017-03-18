#pragma once
#include "cRole.h"
#include <vector>
class Coin :
	public cRole
{
public:
	Coin(float x, float y, float vx, float vy);
	~Coin();
	void Update(float deltaTime);
	void  Draw(HDC hdc);
	void Get();
	float timer;
	bool isGet();
protected:
	TCHAR filename[20];
	int PicControl = 1;
	float FrameCount = 0;
	bool GetCoin;
};

