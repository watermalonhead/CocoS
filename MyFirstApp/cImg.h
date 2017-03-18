#pragma once
#include <tchar.h>
#include "ximage.h"

class cImg
{
private:
	CxImage * mCximg;	// 封装的CxImage
	UINT w,h;			// 图片的高度和宽度
public:
	cImg(TCHAR * filename, ENUM_CXIMAGE_FORMATS format);
	~cImg(void);
	// 在(x,y)处旋转angle°
	void Draw(HDC hdc, UINT x, UINT y, double angle = 0);
	float GetWidth(void);
	float GetHeight(void);
};
