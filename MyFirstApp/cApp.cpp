#include "cApp.h"
#include "cBackground.h"
#include "Mario.h"
#include"MapIStrategy.h"
#include<time.h>
#define GAME_MAIN 1
#define HERO_DIE 2
bool bLastSpaceDown = false;
bool bRunning = true;
int cApp::Mode;
Mario* mario = 0;
RECT MarioRect;
RECT QuitRect;
RECT ReplayRect;
MapIStrategy *Map;
POINT Mouse;
cImg *Start = new cImg(L"素材包\\start2.jpg", CXIMAGE_FORMAT_JPG);
cImg *End = new cImg(L"素材包\\end.png", CXIMAGE_FORMAT_PNG);
cImg *Quit = new cImg(L"素材包\\quit.png", CXIMAGE_FORMAT_PNG);
cImg *Replay = new cImg(L"素材包\\Replay.png", CXIMAGE_FORMAT_PNG);
bool DieSound = false;
RECT cApp::GetRect(cImg *target,float x,float y)
{
	RECT r;
	r.left = x - target->GetWidth() / 2;
	r.top = y - target->GetHeight() / 2;
	r.right = x + target->GetWidth() / 2;
	r.bottom = y + target->GetHeight() / 2;
	return r;
}

cApp::cApp(void)
{
	Mode = 1;
	Speed = 150;
	TriSpeed = 170;
	TurSpeed = 180;
	QueryPerformanceFrequency(&mFrequency);
	QueryPerformanceCounter(&mStartCount);
}

cApp::~cApp(void)
{
}

BOOL cApp::Init(void)
{
	DieSound = false;
	mManager.EraesALL();
	CoinManger.EraesALL();
	mario = NULL;

	srand(time(NULL));
	mhDC = GetDC(GethWnd());
	mhMemDC = CreateCompatibleDC(mhDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(mhDC, m_Width, m_Height);
	SelectObject(mhMemDC, hBitmap);
	DeleteObject(hBitmap);
	SetTextColor(mhMemDC, RGB(255, 0, 0));
	SetBkMode(mhMemDC, TRANSPARENT);

	mManager.mMovableList.push_back(new cBackground(320, 240, Speed, 0));
	mario = new Mario(50, 385, 0, 300); //385
	MarioRect = mario->GetRect();
	mManager.mMovableList.push_back(mario); //把图片加载进list
	int Ran = 1 + rand() % 4;

	if (Ran == 1)
	{
		Map = new Map1(Speed, TriSpeed, TurSpeed, 0);
	}
	else if (Ran == 2)
	{
		Map = new Map2(Speed, TriSpeed, TurSpeed, 0);
	}
	else if (Ran == 4)
	{
		Map = new Map4(Speed, TriSpeed, TurSpeed, 0);
	}
	else if (Ran == 3)
	{
		Map = new Map3(Speed, TriSpeed, TurSpeed, 0);
	}
	return TRUE;
}


BOOL cApp::Frame(void)
{
	GetCursorPos(&Mouse); //获取鼠标位置
	ScreenToClient(h_Wnd,&Mouse);
	static LARGE_INTEGER lastCounter = mStartCount;
	static UINT framesCount = 0;

	LARGE_INTEGER currentCounter;
	QueryPerformanceCounter(&currentCounter);

	// 从开始到现在经过了多少时间
	double totalTime = (double)
		(currentCounter.LowPart - mStartCount.LowPart)
		/ mFrequency.LowPart;

	// 上一帧到现在经过了多少时间
	double deltaTime = (double)
		(currentCounter.LowPart - lastCounter.LowPart)
		/ mFrequency.LowPart;
	lastCounter = currentCounter;
	//放在frame刚进来处，无论什么时候都得获取上一帧时间
#pragma region 开始菜单
	if (Mode == 1)
	{
		Start->Draw(mhDC, 320, 240, 0);
		bool bCurSpaceDown = IsKeyDown(VK_SPACE);
		if (bCurSpaceDown && !bLastSpaceDown)
		{
			bRunning = !bRunning;
			Mode=2;
			delete Start;	
		}
		return TRUE;
	}
#pragma endregion

#pragma region 游戏中

	if (Mode == 2)
	{
		// 如果要暂停，则不继续下面的语句了
		if (GethWnd() != GetForegroundWindow())
			return TRUE;
		bool bCurSpaceDown = IsKeyDown(VK_SPACE);
		if (bCurSpaceDown && !bLastSpaceDown)
		{
			bRunning = !bRunning;
		}
		bLastSpaceDown = bCurSpaceDown;
		if (!bRunning)
		{
			cBackground::sound.Stop(GAME_MAIN);
			cBackground::sound.play(GAME_MAIN);
			return TRUE;
		}


		mManager.Update(deltaTime);//一次性更新
		CoinManger.Update(deltaTime);

		// 将结果显示到字符串
		static TCHAR tempStr[100];

		mManager.Draw(mhMemDC);//一次性Draw
		CoinManger.Draw(mhMemDC);//一次性Draw

		_stprintf(
			tempStr,
			L"瞬时帧率:%8.2lf  平均帧率:%8.2lf",
			1 / deltaTime,
			(++framesCount) / totalTime);
		TextOut(mhMemDC, 0, 0, tempStr, _tcslen(tempStr));		// 显示字符串内容
		_stprintf(tempStr, L"金币数：%.0f", mario->GetCoinCount());
		TextOut(mhMemDC, 0, 15, tempStr, _tcslen(tempStr));
		_stprintf(tempStr, L"生命：%d", mario->GetLife());
		TextOut(mhMemDC, 0, 30, tempStr, _tcslen(tempStr));

		BitBlt(
			mhDC,
			0, 0, m_Width, m_Height,
			mhMemDC,
			0, 0,
			SRCCOPY);

		if (IsKeyDown(VK_ESCAPE))
			return FALSE;

		if (mario->GetLife()<=0||MarioRect.right<0)
		{
			Mode = 3;
		}
		return TRUE;
	}

#pragma endregion

#pragma region Gameover
	if (Mode == 3)
	{
		if (!DieSound)
		{
			cBackground::sound.ReadFile(HERO_DIE, "素材包\\Sound\\死亡1.mp3", DOSOUND);
			cBackground::sound.play(HERO_DIE);
			cBackground::sound.ReadFile(HERO_DIE, "素材包\\Sound\\死亡2.mp3", DOSOUND);
			cBackground::sound.play(HERO_DIE);
			DieSound = true;
		}
		cBackground::sound.Stop(GAME_MAIN);
		End->Draw(mhMemDC, 320, 240, 0);
		Quit->Draw(mhMemDC, 534, 251, 0);
		Replay->Draw(mhMemDC, 68, 251, 0);
		BitBlt(
			mhDC,
			0, 0, m_Width, m_Height,
			mhMemDC,
			0, 0,
			SRCCOPY);
	#pragma region 退出按钮检测
			QuitRect = GetRect(Quit, 534, 251);
			RECT r, MouseRect;
			MouseRect.left = Mouse.x - 1;
			MouseRect.right = Mouse.x + 1;
			MouseRect.top = Mouse.y - 1;
			MouseRect.bottom = Mouse.y + 1;
			if ((IntersectRect(&r, &QuitRect, &MouseRect) == TRUE))
			{
				if (IsKeyDown(VK_LBUTTON))
				{
					return FALSE;
				}
			}
	#pragma endregion

	#pragma region 重试按钮
				ReplayRect = GetRect(Replay, 68, 251);
				if ((IntersectRect(&r, &ReplayRect, &MouseRect) == TRUE))
				{
					if (IsKeyDown(VK_LBUTTON))
					{
						DeleteDC(mhMemDC);
						ReleaseDC(GethWnd(), mhDC);
						Mode = 2;
						cApp::Init();
						return TRUE;
					}
				}
	#pragma endregion
			return TRUE;

	}
#pragma endregion

}

BOOL cApp::ShutDown(void)
{
	delete End;
	delete Quit;
	DeleteDC(mhMemDC);
	ReleaseDC(GethWnd(), mhDC);
	return TRUE;
}

bool cApp::IsKeyDown(int keyCode)
{
	return (GetAsyncKeyState(keyCode) & 0x8000) != 0;
}
