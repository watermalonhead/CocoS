#include "cMovableMgr.h"
#include"Pipe.h"
#include"Mario.h"
#include"cApp.h"
#include"Turtle.h"
#include"Brick.h"
#define ENEMY_DIE 1
#define GET_COIN 2
Mario* Hero = NULL;
Pipe* Pipetemp;
cTriangle* Tritemp;
Turtle* Turtletemp;
Brick* Britemp;
CSoundManage cMovableMgr::sound;
cMovableMgr::cMovableMgr()
{
}

void cMovableMgr::EraesALL()
{
	MovableListType::iterator it = mMovableList.begin(), end = mMovableList.end();
	for (; it != end; it++)
	{
		//Mario* m = dynamic_cast<Mario*>(*it);
		//if (m == NULL)
		//{
		//	delete(*it);
		//}
		delete(*it);
	}
	mMovableList.clear();
}

cMovableMgr::~cMovableMgr()
{

	MovableListType::iterator it = mMovableList.begin(), end = mMovableList.end();
	for (; it != end; it++)
		delete(*it);
}



void cMovableMgr::Draw(HDC hdc)
{
	MovableListType::iterator it = mMovableList.begin(), end = mMovableList.end();
	for (; it != end; it++)
		(*it)->Draw(hdc);
}

void cMovableMgr::Erase(IMovable* target)  //对象移出列表
{
	MovableListType::iterator it = mMovableList.begin(), end = mMovableList.end();
	for (; it != end; it++)
	{
		if (*it == target)
		{
			mMovableList.erase(it);
			break;
		}
	}
}
void cMovableMgr::Update(float deltaTime)//temp当前，it下一个
{

	MovableListType::iterator it = mMovableList.begin(), end = mMovableList.end(), temp;
	for (; it != end;)
	{
		temp = it;
		it++;
		// todo: delete if out of boundary
		if (!RestrictInBoundary((*temp)->GetRect()))//越界释放对象
		{
			//Mario* m = dynamic_cast<Mario*>(*temp);
			//if (m == NULL)
			//{
			//	delete (*temp);
			//	mMovableList.erase(temp);
			//}
			delete (*temp);
			mMovableList.erase(temp);
		}
		else
		{
			(*temp)->Update(deltaTime); //未越界更新对象
		}
	}
	//判断马里奥与物体碰撞
#pragma region 找到马里奥

	it = mMovableList.begin(), end = mMovableList.end();

	for (; it != end;)
	{
		if (Hero != NULL)
		{
			break;
		}
		temp = it;
		it++;
		Hero = dynamic_cast<Mario*>(*temp);
	}
#pragma endregion

	it = mMovableList.begin(), end = mMovableList.end();
	for (; it != end;)
	{
		temp = it;
		it++;
#pragma region 马里奥与金币碰撞
		Coin* coin = dynamic_cast<Coin*>(*temp);
		if (coin != NULL&&!coin->isGet())
		{
			if (isCollisionCoin(Hero, temp))
			{
				coin->Get();

			}
			// 如果碰撞了变成变换图片
		}
#pragma endregion

#pragma region 与栗子头碰撞检测
		cTriangle* Triangle = dynamic_cast<cTriangle*>(*temp);
		if (Triangle != NULL)
		{
			Tritemp = Triangle;
			// 如果碰撞了变成死亡图片
			if (isCollisionTriangel(Hero, Triangle))
			{
				Triangle->Death();
			}
		}
#pragma endregion

#pragma region 马里奥与乌龟碰撞
		Turtle* turtle = dynamic_cast<Turtle*>(*temp);
		if (turtle != NULL)
		{
			Turtletemp = turtle;
			// 如果碰撞了变成死亡图片
			if (isCollisionTurtle(Hero, turtle))
			{
				turtle->Death();
			}
		}

#pragma endregion

#pragma region 马里奥与花碰撞
		Enemy* flower = dynamic_cast<Enemy*>(*temp);
		if (flower != NULL)
		{
			if (isCollisionflower(Hero, flower))
			{
				if (Hero->GetLife() <= 0)
				{
					Hero->SetImg(cImgManager::CreateImg(L"素材包\\over.png", CXIMAGE_FORMAT_PNG));
				}
			}
		}
#pragma endregion

#pragma region 与静态物品碰撞检测

#pragma region 管道部分
		Pipe* pipe = dynamic_cast<Pipe*>(*temp);

		if (pipe != NULL)
		{
			Pipetemp = pipe;
			// 如果碰撞了就速度和水管一样
			if (isCollisionItem(Hero, pipe))
			{
				Hero->ChangeSpeed(pipe->GetSpeed());
			}
			if (Pipetemp != NULL&&Tritemp != NULL)
			{
				if (isCollisionEnemy(Tritemp, Pipetemp))
				{
					Tritemp->ChangeSpeed(Pipetemp->GetSpeed());
				}
			}
			if (Pipetemp != NULL&& Turtletemp != NULL)
			{
				if (isCollisionEnemy(Turtletemp, Pipetemp))
				{
					Turtletemp->ChangeSpeed(Pipetemp->GetSpeed());
				}
			}
		}
#pragma endregion

#pragma region 砖块部分
		Brick* brick = dynamic_cast<Brick*>(*temp);

		if (brick != NULL)
		{
			Britemp = brick;
			// 如果碰撞了就速度和水管一样
			if (isCollisionItem(Hero, brick))
			{
				Hero->ChangeSpeed(brick->GetSpeed());
			}
			if (Britemp != NULL&&Tritemp != NULL)
			{
				if (isCollisionEnemy(Tritemp, Britemp))
				{
					Tritemp->ChangeSpeed(Britemp->GetSpeed());
				}
			}
			if (Pipetemp != NULL&& Turtletemp != NULL)
			{
				if (isCollisionEnemy(Turtletemp, Britemp))
				{
					Turtletemp->ChangeSpeed(Britemp->GetSpeed());
				}
			}
		}
#pragma endregion


#pragma endregion



	}
}
//马里奥物体碰撞
bool cMovableMgr::isCollisionItem(Mario* Hero, IMovable* target)
{
	RECT Mario, Target;
	Mario = Hero->GetRect();
	Target = target->GetRect();
	static bool isUp = false;
	if ((Target.left - Mario.right<2) && (Mario.bottom>Target.top) && (Hero->GetPos().x <= Target.left))//在左边碰撞bug修正
	{
		return true;
	}
	else if ((Target.left - Mario.right < 2) && (Mario.bottom<Target.top) && (Hero->GetPos().x <= Target.left))//在左边碰撞
	{
		Hero->ChangeSpeed(0);
	}
	else if ((Hero->GetPos().x >= Target.left) && (Hero->GetPos().x <= Target.right) && (Mario.bottom>Target.top))
	{
		float high = Target.top - Hero->GetHeight();
		isUp = cApp::IsKeyDown(VK_UP);
		if (!isUp)
		{
			Hero->ChangeUp();
			Hero->ChangeHigh(high);
		}
	}
	return false;
}
//马里奥与板栗仔碰撞
bool cMovableMgr::isCollisionTriangel(Mario* Hero, cTriangle* target)
{
	RECT Mario, Target;
	Mario = Hero->GetRect();
	Target = target->GetRect();
	if ((Target.left - Mario.right<2) && (Mario.bottom>Target.top) && (Hero->GetPos().x <= Target.left)) //马里奥生命-1,后暂时无敌5s 左
	{
		if (!target->isCollision)
		{
			Hero->HeroHurt();
			target->isCollision = true;
		}
		if (Hero->GetLife() <= 0)
		{
			Hero->SetImg(cImgManager::CreateImg(L"素材包\\over.png", CXIMAGE_FORMAT_PNG));
		}
		return false;
	}
	else if ((Hero->GetPos().x >= Target.left) && (Hero->GetPos().x <= Target.right) && (Mario.bottom - Target.top <= 2) && (Mario.bottom - Target.top >= 0))//马里奥踩到头，栗子死亡
	{
		float high = Target.top - Hero->GetHeight();
		Hero->ChangeHigh(high);
		Hero->ChangeCurrentUp();
		Hero->ChangeUp();
		target->LifeHurt();
		target->SetImg(cImgManager::CreateImg(L"素材包\\triangle3.png", CXIMAGE_FORMAT_PNG));
		sound.ReadFile(ENEMY_DIE, "素材包\\Sound\\踩敌人.mp3", DOSOUND);
		sound.play(ENEMY_DIE);
		return true;
	}
}
//马里奥和金币碰撞
bool cMovableMgr::isCollisionCoin(Mario* Hero, MovableListType::iterator it)
{
	RECT r, targetRect = (*it)->GetRect(), HeroRect = (Hero)->GetRect();
	if (IntersectRect(&r, &targetRect, &HeroRect) == TRUE)
	{
		// 捡金币
		(*it)->SetImg(cImgManager::CreateImg(L"素材包\\coin3.png", CXIMAGE_FORMAT_PNG));
		Hero->CoinAdd();
		sound.ReadFile(GET_COIN, "素材包\\Sound\\金币.mp3", DOSOUND);
		sound.play(GET_COIN);
		return true;
	}
	return false;
}
//马里奥与乌龟碰撞
bool cMovableMgr::isCollisionTurtle(Mario* Hero, Turtle* target)
{
	RECT Mario, Target;
	Mario = Hero->GetRect();
	Target = target->GetRect();
	if ((Target.left - Mario.right<2) && (Mario.bottom>Target.top) && (Hero->GetPos().x <= Target.left)) //马里奥生命-1,后暂时无敌5s 左
	{
		if (!target->isCollision)
		{
			Hero->HeroHurt();
			target->isCollision = true;
		}
		if (Hero->GetLife() <= 0)
		{
			Hero->SetImg(cImgManager::CreateImg(L"素材包\\over.png", CXIMAGE_FORMAT_PNG));
		}
		return false;
	}
	else if ((Hero->GetPos().x >= Target.left) && (Hero->GetPos().x <= Target.right) && (Mario.bottom - Target.top <= 2) && (Mario.bottom - Target.top >= 0))//马里奥踩到头，栗子死亡
	{
		float high = Target.top - Hero->GetHeight();
		Hero->ChangeHigh(high);
		Hero->ChangeCurrentUp();
		Hero->ChangeUp();
		target->LifeHurt();
		target->SetImg(cImgManager::CreateImg(L"素材包\\Turtle3.png", CXIMAGE_FORMAT_PNG));
		sound.ReadFile(ENEMY_DIE, "素材包\\Sound\\踩敌人.mp3", DOSOUND);
		sound.play(ENEMY_DIE);
		return true;
	}
}
//马里奥和花碰撞
bool cMovableMgr::isCollisionflower(Mario* Hero, Enemy* target)
{
	RECT r, targetRect = target->GetRect(), HeroRect = (Hero)->GetRect();
	if (IntersectRect(&r, &targetRect, &HeroRect) == TRUE)
	{
		// 命中
		if (!target->isCollision)
		{
			Hero->HeroHurt();
			target->isCollision = true;
		}
		return true;
	}
	return false;
}
//怪物和障碍物碰撞
bool cMovableMgr::isCollisionEnemy(IMovable* Enemy, IMovable* target)
{
	RECT r, targetRect = target->GetRect(), EnemyRect = (Enemy)->GetRect();
	if (IntersectRect(&r, &targetRect, &EnemyRect) == TRUE)
	{
		// 碰撞了
		return true;
	}
}