#include "Engine_System.h"
#include "cApp.h"

int WINAPI _tWinMain(HINSTANCE hInstance,
					 HINSTANCE hPreInstance,
					 LPTSTR lpCmdLine,
					 int nCmdShow)
{
	cApplication* game;
	game = new cApp();
	game->Run();
	delete game;

}




