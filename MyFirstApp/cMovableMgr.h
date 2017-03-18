#pragma once
#include "Engine_System.h"
#include "IMovable.h"
#include <list>
#include"Mario.h"
#include"cTriangle.h"
#include"Turtle.h"
#include"Coin.h"
#include"Enemy.h"
#include "sound\\Soundmanage.h"
using namespace std;

class cMovableMgr
{
public:
	typedef list<IMovable *> MovableListType;
	MovableListType mMovableList;
public:
	cMovableMgr();
	~cMovableMgr();
	void Draw(HDC hdc);
	void Update(float deltaTime);
	bool isCollisionItem(Mario* Hero, IMovable* target);//�������뾲̬��Ʒ��ײ
	bool isCollisionTriangel(Mario* Hero, cTriangle* target);//�����������ͷ��ײ
	bool isCollisionCoin(Mario* Hero, MovableListType::iterator it);//�����������ײ
	bool isCollisionTurtle(Mario* Hero, Turtle* target);//��������ڹ���ײ
	bool isCollisionflower(Mario* Hero, Enemy* target);//������뻨��ײ
	bool isCollisionEnemy(IMovable* Enemy, IMovable* target);//���������ϰ���ײ
	void Erase(IMovable* target);//�������
	void EraesALL();
	static CSoundManage sound;
	UINT GetMovableCount()
	{
		return mMovableList.size();
	}
};

