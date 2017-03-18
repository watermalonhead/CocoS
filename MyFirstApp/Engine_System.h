#pragma once
#include <windows.h>
#include <tchar.h>

class cApplication
{
protected:
	HINSTANCE h_Inst;
	HWND h_Wnd;
	TCHAR m_Class[MAX_PATH];
	TCHAR m_Caption[MAX_PATH];

public:
	cApplication(void);
	~cApplication(void);
	HWND GethWnd(void);
	HINSTANCE GethInstance(void);
	BOOL Run(void);
	BOOL ReSize(long Width, long Height);

	virtual BOOL Init(void)
	{
		return TRUE;
	}

	virtual BOOL Frame(void)
	{
		return TRUE;
	}

	virtual BOOL ShutDown(void)
	{
		return TRUE;
	}
protected:
	// 客户区宽度
	int m_Width;
	// 客户区高度
	int m_Height;
};

LRESULT CALLBACK AppWindowProc(HWND hWnd,
							   UINT msg,
							   WPARAM wParam,
							   LPARAM lParam);
BOOL RestrictInBoundary(RECT r);