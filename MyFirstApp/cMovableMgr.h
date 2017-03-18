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
	bool isCollisionItem(Mario* Hero, IMovable* target);//马丽奥与静态物品碰撞
	bool isCollisionTriangel(Mario* Hero, cTriangle* target);//马里奥与栗子头碰撞
	bool isCollisionCoin(Mario* Hero, MovableListType::iterator it);//马里奥与金币碰撞
	bool isCollisionTurtle(Mario* Hero, Turtle* target);//马里奥与乌龟碰撞
	bool isCollisionflower(Mario* Hero, Enemy* target);//马里奥与花碰撞
	bool isCollisionEnemy(IMovable* Enemy, IMovable* target);//怪物与与障碍碰撞
	void Erase(IMovable* target);//清除对象
	void EraesALL();
	static CSoundManage sound;
	UINT GetMovableCount()
	{
		return mMovableList.size();
	}
};

