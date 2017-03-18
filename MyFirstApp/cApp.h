#pragma once
#include "engine_system.h"
#include "cMovableMgr.h"

class cApp :
	public cApplication
{
public:
	cApp(void);
	~cApp(void);
	BOOL Init(void);
	BOOL Frame(void);
	BOOL ShutDown(void);
private:
	// 设备DC
	HDC mhDC;
	// 内存DC
	HDC mhMemDC;
protected:
	// 频率
	LARGE_INTEGER mFrequency;
	// 开始的数
	LARGE_INTEGER mStartCount;
public:
	static bool IsKeyDown(int keyCode);
public:
	static cMovableMgr mManager;
	static cMovableMgr CoinManger;//管理金币
	static float Speed;
	static float TriSpeed;
	static float TurSpeed;
	static int Mode;
	RECT GetRect(cImg *target, float x, float y);
};
