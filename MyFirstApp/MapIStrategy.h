#pragma once
#include"Coin.h"
#include"cTriangle.h"
#include"Turtle.h"
#include"Enemy.h"
#include"Pipe.h"
#include"cApp.h"
#include"Brick.h"
class MapIStrategy
{
public:
	MapIStrategy();
	~MapIStrategy();
};

class Map1: public MapIStrategy
{
public:
	Map1(float Speed, float TriSpeed, float TurSpeed, float fix);
	~Map1();
};

class Map2 : public MapIStrategy
{
public:
	Map2(float Speed, float TriSpeed, float TurSpeed, float fix);
	~Map2();
};

class Map3 : public MapIStrategy
{
public:
	Map3(float Speed, float TriSpeed, float TurSpeed, float fix);
	~Map3();
};

class Map4 : public MapIStrategy
{
public:
	Map4(float Speed, float TriSpeed, float TurSpeed, float fix);
	~Map4();
};




