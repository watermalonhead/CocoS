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

void cMovableMgr::Erase(IMovable* target)  //�����Ƴ��б�
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
void cMovableMgr::Update(float deltaTime)//temp��ǰ��it��һ��
{

	MovableListType::iterator it = mMovableList.begin(), end = mMovableList.end(), temp;
	for (; it != end;)
	{
		temp = it;
		it++;
		// todo: delete if out of boundary
		if (!RestrictInBoundary((*temp)->GetRect()))//Խ���ͷŶ���
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
			(*temp)->Update(deltaTime); //δԽ����¶���
		}
	}
	//�ж��������������ײ
#pragma region �ҵ������

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
#pragma region �����������ײ
		Coin* coin = dynamic_cast<Coin*>(*temp);
		if (coin != NULL&&!coin->isGet())
		{
			if (isCollisionCoin(Hero, temp))
			{
				coin->Get();

			}
			// �����ײ�˱�ɱ任ͼƬ
		}
#pragma endregion

#pragma region ������ͷ��ײ���
		cTriangle* Triangle = dynamic_cast<cTriangle*>(*temp);
		if (Triangle != NULL)
		{
			Tritemp = Triangle;
			// �����ײ�˱������ͼƬ
			if (isCollisionTriangel(Hero, Triangle))
			{
				Triangle->Death();
			}
		}
#pragma endregion

#pragma region ��������ڹ���ײ
		Turtle* turtle = dynamic_cast<Turtle*>(*temp);
		if (turtle != NULL)
		{
			Turtletemp = turtle;
			// �����ײ�˱������ͼƬ
			if (isCollisionTurtle(Hero, turtle))
			{
				turtle->Death();
			}
		}

#pragma endregion

#pragma region ������뻨��ײ
		Enemy* flower = dynamic_cast<Enemy*>(*temp);
		if (flower != NULL)
		{
			if (isCollisionflower(Hero, flower))
			{
				if (Hero->GetLife() <= 0)
				{
					Hero->SetImg(cImgManager::CreateImg(L"�زİ�\\over.png", CXIMAGE_FORMAT_PNG));
				}
			}
		}
#pragma endregion

#pragma region �뾲̬��Ʒ��ײ���

#pragma region �ܵ�����
		Pipe* pipe = dynamic_cast<Pipe*>(*temp);

		if (pipe != NULL)
		{
			Pipetemp = pipe;
			// �����ײ�˾��ٶȺ�ˮ��һ��
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

#pragma region ש�鲿��
		Brick* brick = dynamic_cast<Brick*>(*temp);

		if (brick != NULL)
		{
			Britemp = brick;
			// �����ײ�˾��ٶȺ�ˮ��һ��
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
//�����������ײ
bool cMovableMgr::isCollisionItem(Mario* Hero, IMovable* target)
{
	RECT Mario, Target;
	Mario = Hero->GetRect();
	Target = target->GetRect();
	static bool isUp = false;
	if ((Target.left - Mario.right<2) && (Mario.bottom>Target.top) && (Hero->GetPos().x <= Target.left))//�������ײbug����
	{
		return true;
	}
	else if ((Target.left - Mario.right < 2) && (Mario.bottom<Target.top) && (Hero->GetPos().x <= Target.left))//�������ײ
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
//��������������ײ
bool cMovableMgr::isCollisionTriangel(Mario* Hero, cTriangle* target)
{
	RECT Mario, Target;
	Mario = Hero->GetRect();
	Target = target->GetRect();
	if ((Target.left - Mario.right<2) && (Mario.bottom>Target.top) && (Hero->GetPos().x <= Target.left)) //���������-1,����ʱ�޵�5s ��
	{
		if (!target->isCollision)
		{
			Hero->HeroHurt();
			target->isCollision = true;
		}
		if (Hero->GetLife() <= 0)
		{
			Hero->SetImg(cImgManager::CreateImg(L"�زİ�\\over.png", CXIMAGE_FORMAT_PNG));
		}
		return false;
	}
	else if ((Hero->GetPos().x >= Target.left) && (Hero->GetPos().x <= Target.right) && (Mario.bottom - Target.top <= 2) && (Mario.bottom - Target.top >= 0))//����²ȵ�ͷ����������
	{
		float high = Target.top - Hero->GetHeight();
		Hero->ChangeHigh(high);
		Hero->ChangeCurrentUp();
		Hero->ChangeUp();
		target->LifeHurt();
		target->SetImg(cImgManager::CreateImg(L"�زİ�\\triangle3.png", CXIMAGE_FORMAT_PNG));
		sound.ReadFile(ENEMY_DIE, "�زİ�\\Sound\\�ȵ���.mp3", DOSOUND);
		sound.play(ENEMY_DIE);
		return true;
	}
}
//����ºͽ����ײ
bool cMovableMgr::isCollisionCoin(Mario* Hero, MovableListType::iterator it)
{
	RECT r, targetRect = (*it)->GetRect(), HeroRect = (Hero)->GetRect();
	if (IntersectRect(&r, &targetRect, &HeroRect) == TRUE)
	{
		// ����
		(*it)->SetImg(cImgManager::CreateImg(L"�زİ�\\coin3.png", CXIMAGE_FORMAT_PNG));
		Hero->CoinAdd();
		sound.ReadFile(GET_COIN, "�زİ�\\Sound\\���.mp3", DOSOUND);
		sound.play(GET_COIN);
		return true;
	}
	return false;
}
//��������ڹ���ײ
bool cMovableMgr::isCollisionTurtle(Mario* Hero, Turtle* target)
{
	RECT Mario, Target;
	Mario = Hero->GetRect();
	Target = target->GetRect();
	if ((Target.left - Mario.right<2) && (Mario.bottom>Target.top) && (Hero->GetPos().x <= Target.left)) //���������-1,����ʱ�޵�5s ��
	{
		if (!target->isCollision)
		{
			Hero->HeroHurt();
			target->isCollision = true;
		}
		if (Hero->GetLife() <= 0)
		{
			Hero->SetImg(cImgManager::CreateImg(L"�زİ�\\over.png", CXIMAGE_FORMAT_PNG));
		}
		return false;
	}
	else if ((Hero->GetPos().x >= Target.left) && (Hero->GetPos().x <= Target.right) && (Mario.bottom - Target.top <= 2) && (Mario.bottom - Target.top >= 0))//����²ȵ�ͷ����������
	{
		float high = Target.top - Hero->GetHeight();
		Hero->ChangeHigh(high);
		Hero->ChangeCurrentUp();
		Hero->ChangeUp();
		target->LifeHurt();
		target->SetImg(cImgManager::CreateImg(L"�زİ�\\Turtle3.png", CXIMAGE_FORMAT_PNG));
		sound.ReadFile(ENEMY_DIE, "�زİ�\\Sound\\�ȵ���.mp3", DOSOUND);
		sound.play(ENEMY_DIE);
		return true;
	}
}
//����ºͻ���ײ
bool cMovableMgr::isCollisionflower(Mario* Hero, Enemy* target)
{
	RECT r, targetRect = target->GetRect(), HeroRect = (Hero)->GetRect();
	if (IntersectRect(&r, &targetRect, &HeroRect) == TRUE)
	{
		// ����
		if (!target->isCollision)
		{
			Hero->HeroHurt();
			target->isCollision = true;
		}
		return true;
	}
	return false;
}
//������ϰ�����ײ
bool cMovableMgr::isCollisionEnemy(IMovable* Enemy, IMovable* target)
{
	RECT r, targetRect = target->GetRect(), EnemyRect = (Enemy)->GetRect();
	if (IntersectRect(&r, &targetRect, &EnemyRect) == TRUE)
	{
		// ��ײ��
		return true;
	}
}