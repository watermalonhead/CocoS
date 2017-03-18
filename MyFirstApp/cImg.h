#pragma once
#include <tchar.h>
#include "ximage.h"

class cImg
{
private:
	CxImage * mCximg;	// ��װ��CxImage
	UINT w,h;			// ͼƬ�ĸ߶ȺͿ��
public:
	cImg(TCHAR * filename, ENUM_CXIMAGE_FORMATS format);
	~cImg(void);
	// ��(x,y)����תangle��
	void Draw(HDC hdc, UINT x, UINT y, double angle = 0);
	float GetWidth(void);
	float GetHeight(void);
};
