#pragma once
#include "cRole.h"
class Pipe :
	public cRole
{
public:
	Pipe(float x, float y, float vx, float vy);
	~Pipe();
	void Update(float deltaTime);
	void  Draw(HDC hdc);
};

