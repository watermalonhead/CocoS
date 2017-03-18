#include "MapIStrategy.h"
cMovableMgr cApp::mManager;//静态类外声明
cMovableMgr cApp::CoinManger;

MapIStrategy::MapIStrategy()
{
}


MapIStrategy::~MapIStrategy()
{
}

//=========================Map1
Map1::Map1(float Speed, float TriSpeed, float TurSpeed, float fix)
{


	cApp::CoinManger.mMovableList.push_back(new Coin(350 + fix, 270, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(380 + fix, 270, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(410 + fix, 270, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(440 + fix, 270, Speed, 0));
	//间隔30
	cApp::CoinManger.mMovableList.push_back(new Coin(350 + fix, 300, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(380 + fix, 300, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(410 + fix, 300, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(440 + fix, 300, Speed, 0));

	cApp::CoinManger.mMovableList.push_back(new Coin(350 + fix, 330, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(380 + fix, 330, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(410 + fix, 330, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(440 + fix, 330, Speed, 0));
	//
	cApp::mManager.mMovableList.push_back(new Turtle(600 + fix, 395, TurSpeed, 0));

	cApp::mManager.mMovableList.push_back(new cTriangle(400 + fix, 395, TriSpeed, 0));

	cApp::mManager.mMovableList.push_back(new Pipe(250 + fix, 390, Speed, 0));
}

//=======================Map2
Map2::Map2(float Speed, float TriSpeed, float TurSpeed, float fix)
{
	cApp::mManager.mMovableList.push_back(new Enemy(200 + fix, 393, Speed, 0));
	cApp::mManager.mMovableList.push_back(new Turtle(350 + fix, 395, TurSpeed, 0));
	cApp::mManager.mMovableList.push_back(new cTriangle(550 + fix, 395, TriSpeed, 0));
	cApp::mManager.mMovableList.push_back(new Pipe(400 + fix, 390, Speed, 0));
	//金币
	cApp::CoinManger.mMovableList.push_back(new Coin(400 + fix, 240, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(400 + fix, 270, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(400 + fix, 300, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(350 + fix, 270, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(450 + fix, 270, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(300 + fix, 300, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(500 + fix, 300, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(400 + fix, 330, Speed, 0));
}

//======================Map3
Map3::Map3(float Speed, float TriSpeed, float TurSpeed, float fix)
{
	cApp::mManager.mMovableList.push_back(new Brick(340 + fix, 400, Speed, 0));
	cApp::mManager.mMovableList.push_back(new Brick(310 + fix, 400, Speed, 0));
	cApp::mManager.mMovableList.push_back(new Brick(280 + fix, 400, Speed, 0));
	cApp::mManager.mMovableList.push_back(new Pipe(380 + fix, 390, Speed, 0));

	cApp::mManager.mMovableList.push_back(new Enemy(460 + fix, 393, Speed, 0));
	cApp::mManager.mMovableList.push_back(new cTriangle(580 + fix, 393, TriSpeed, 0));

	cApp::CoinManger.mMovableList.push_back(new Coin(540 + fix, 330, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(540 + fix, 300, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(540 + fix, 270, Speed, 0));
}

//======================Map4
Map4::Map4(float Speed, float TriSpeed, float TurSpeed, float fix)
{
	cApp::mManager.mMovableList.push_back(new Pipe(200 + fix, 390, Speed, 0));
	cApp::mManager.mMovableList.push_back(new Pipe(500 + fix, 390, Speed, 0));
	cApp::mManager.mMovableList.push_back(new Turtle(150 + fix, 395, TurSpeed, 0));
	cApp::mManager.mMovableList.push_back(new cTriangle(400 + fix, 395, TriSpeed, 0));

	cApp::CoinManger.mMovableList.push_back(new Coin(300 + fix, 200, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(300 + fix, 250, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(350 + fix, 250, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(300 + fix, 300, Speed, 0));

	cApp::CoinManger.mMovableList.push_back(new Coin(400 + fix, 200, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(400 + fix, 250, Speed, 0));
	cApp::CoinManger.mMovableList.push_back(new Coin(400 + fix, 300, Speed, 0));
}


