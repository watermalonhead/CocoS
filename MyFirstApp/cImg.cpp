#include "cImg.h"

cImg::cImg(TCHAR * filename, ENUM_CXIMAGE_FORMATS format)
{
	mCximg = new CxImage;
	if (mCximg->Load(filename, format))
	{
		w = mCximg->GetWidth();
		h = mCximg->GetHeight();
	}
	else
	{
		mCximg = NULL;
		w = 0;
		h = 0;
	}
}

cImg::~cImg(void)
{
	if (mCximg)
	{
		delete mCximg;
		mCximg = NULL;
	}
}

void cImg::Draw(HDC hdc, UINT x, UINT y, double angle)
{
	if (!mCximg) return;

	//angle -= 90;
	if (fabs(angle) < 1e-6)
	{
		mCximg->Draw(hdc,x-w/2,y-h/2);
	} 
	else
	{
		CxImage temp;
		mCximg->Rotate(angle, &temp);
		temp.Draw(hdc, x-temp.GetWidth()/2,y-temp.GetHeight()/2);
	}
}

float cImg::GetWidth(void)
{
	return w;
}

float cImg::GetHeight(void)
{
	return h;
}
