#include "cRole.h"
#include "cImgManager.h"


cRole::cRole(float x, float y, float vx, float vy)
: IMovable(x, y, vx, vy)
{
	mLife = 1;
}


cRole::~cRole()
{
}
