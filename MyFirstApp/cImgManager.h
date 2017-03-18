#pragma once
#include <map>
#include <string>
#include "cImg.h"
using namespace std;

class cImgManager
{
protected:
	typedef map<wstring, cImg*> ImgMap;
	static ImgMap mImgMap;
public:
	cImgManager();
	~cImgManager();

	static cImg* CreateImg(TCHAR* fileName, DWORD format);

	static int GetSize()
	{
		return mImgMap.size();
	}
};

