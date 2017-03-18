#include "Engine_System.h"

cApplication::cApplication(void)
: m_Width(640)
, m_Height(480)
{
	// 获取模块句柄
	h_Inst = GetModuleHandle(NULL);

	// 设置类名和标题字符串
	_tcscpy(m_Class, L"Mario");
	_tcscpy(m_Caption, L"Mario");

#pragma region 定义并注册窗口
	WNDCLASSEX wcex = {0};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = h_Inst;
	wcex.lpfnWndProc = (WNDPROC)AppWindowProc;
	wcex.lpszClassName = m_Class;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	RegisterClassEx(&wcex);
#pragma endregion
}

cApplication::~cApplication(void)
{
}

HWND cApplication::GethWnd(void)
{
	return h_Wnd;
}

HINSTANCE cApplication::GethInstance(void)
{
	return h_Inst;
}

BOOL cApplication::Run(void)
{
#pragma region 生成并显示窗口
	HWND hWnd = CreateWindow(
		m_Class,
		m_Caption,
		WS_OVERLAPPEDWINDOW,
		0,0,m_Width,m_Height,
		HWND_DESKTOP,
		NULL,
		h_Inst,
		NULL);
	if (!hWnd) return FALSE;
	h_Wnd=hWnd;

	ReSize(m_Width,m_Height);

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

#pragma endregion

	if (Init()==TRUE){
#pragma region 消息循环
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while(msg.message != WM_QUIT){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// do something
			if (Frame() == FALSE)
				break;
		}
	}

#pragma endregion
	}

	ShutDown();

}

BOOL cApplication::ReSize(long Width, long Height)
{
	int xFrame   = GetSystemMetrics(SM_CXFRAME);
	int yFrame   = GetSystemMetrics(SM_CYFRAME);
	int yCaption = GetSystemMetrics(SM_CYCAPTION);
	int xScreen	 = GetSystemMetrics(SM_CXSCREEN);
	int yScreen  = GetSystemMetrics(SM_CYSCREEN);

	int cw = xFrame + Width + xFrame;
	int ch = yFrame + yCaption + Height + yFrame;

	SetWindowPos(h_Wnd, HWND_TOP, (xScreen-cw)/2, (yScreen - ch)/2, cw, ch, SWP_SHOWWINDOW);
	return TRUE;
}

LRESULT CALLBACK AppWindowProc(HWND hWnd,
							   UINT msg,
							   WPARAM wParam,
							   LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

BOOL RestrictInBoundary(RECT r) //是否在框内
{
	RECT ir;
	RECT boundary = { -5, -5, 1200 + 5, 480 + 5 };
	return IntersectRect(&ir, &boundary, &r);
}
