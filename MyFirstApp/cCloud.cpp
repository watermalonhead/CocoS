#include "cCloud.h"


cCloud::cCloud(float x, float y, float vx, float vy)
: IMovable(x, y, vx, vy)
{
	SetImg(cImgManager::CreateImg(L"ËØ²Ä°ü\\cloud3.png", CXIMAGE_FORMAT_PNG));
}


cCloud::~cCloud()
{
}
