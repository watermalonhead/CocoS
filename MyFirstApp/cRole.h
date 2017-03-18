#pragma once
#include "IMovable.h"
class cRole :
	public IMovable
{
public:
	cRole(float x, float y, float vx, float vy);
	~cRole();
	void Update();
	int GetLife() { return mLife; };
protected:
	int mLife;

};

