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
	// �豸DC
	HDC mhDC;
	// �ڴ�DC
	HDC mhMemDC;
protected:
	// Ƶ��
	LARGE_INTEGER mFrequency;
	// ��ʼ����
	LARGE_INTEGER mStartCount;
public:
	static bool IsKeyDown(int keyCode);
public:
	static cMovableMgr mManager;
	static cMovableMgr CoinManger;//������
	static float Speed;
	static float TriSpeed;
	static float TurSpeed;
	static int Mode;
	RECT GetRect(cImg *target, float x, float y);
};
