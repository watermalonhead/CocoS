#include "cImgManager.h"


cImgManager::cImgManager()
{
}


cImgManager::~cImgManager()
{
}


cImg* cImgManager::CreateImg(TCHAR* fileName, DWORD format)
{
	cImg* tempImg = NULL;
	wstring str = wstring(fileName);
	tempImg = mImgMap[str];

	if (!tempImg)
	{
		// û�����ͼƬ
		tempImg = new cImg(fileName, (ENUM_CXIMAGE_FORMATS)format);
		mImgMap[str] = tempImg;
		return tempImg;
	}
	else
	{
		return tempImg;
	}
}


cImgManager::ImgMap cImgManager::mImgMap;