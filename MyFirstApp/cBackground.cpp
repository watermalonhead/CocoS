	#include "cBackground.h"
#include "cImgManager.h"
#include"MapIStrategy.h"
#include"cApp.h"
#include<time.h>
float timecount=0;
#define GAME_MAIN 1

float cApp::Speed;
float cApp::TriSpeed;
float cApp::TurSpeed;//����
CSoundManage cBackground::sound;
cBackground::cBackground(float x, float y, float vx, float vy)
: IMovable(x, y, vx, vy)
{
	SetImg(cImgManager::CreateImg(L"�زİ�\\test.jpg", CXIMAGE_FORMAT_JPG));
	sound.ReadFile(GAME_MAIN, "�زİ�\\Sound\\bgmfix.wav", DOSOUND);
	sound.play(GAME_MAIN);
}


cBackground::~cBackground()
{
}

void cBackground::Update(float deltaTime)
{
	timecount += deltaTime;
	if (timecount>=117)
	{
		sound.play(GAME_MAIN);
		timecount = 0;
	}
	mPos.x -= xSpeed*deltaTime;
}

void cBackground::Draw(HDC hdc)
{
	srand(time(NULL));
	int RanMap;
	MapIStrategy *Map;
	RanMap = 1 + rand() % 4;
	mImg->Draw(hdc, mPos.x, mPos.y, mPos.angle);
	RECT r=GetRect();
	if (r.right<640)
	{
		if (!isReDraw)//ѭ������
		{
			if (RanMap == 1)
			{
				Map = new Map1(cApp::Speed, cApp::TriSpeed, cApp::TurSpeed, 600);
			}
			else if (RanMap == 2)
			{
				Map = new Map2(cApp::Speed, cApp::TriSpeed, cApp::TurSpeed, 600);
			}
			else if (RanMap == 3)
			{
				Map = new Map3(cApp::Speed, cApp::TriSpeed, cApp::TurSpeed, 600);
			}
			else if (RanMap == 4)
			{
				Map = new Map4(cApp::Speed, cApp::TriSpeed, cApp::TurSpeed, 600);
			}
			isReDraw = true;
		}
		mImg->Draw(hdc, mPos.x + mWidth, mPos.y, mPos.angle);
	}//��r.right��ûС��0ʱ���һ�����油��
	if (r.right<0)
	{
	
		isReDraw = false;
		mPos.x += mWidth;
	}
}