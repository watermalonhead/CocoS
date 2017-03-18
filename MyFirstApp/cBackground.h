#pragma once
#include "IMovable.h"
#include "sound\\Soundmanage.h"
class cBackground :
	public IMovable
{
public:
	cBackground(float x, float y, float vx, float vy);
	~cBackground();
	static CSoundManage sound;
	void Update(float deltaTime);
	void Draw(HDC hdc);
	bool isReDraw = false;
};

