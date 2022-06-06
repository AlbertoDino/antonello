#include "..\rde_engine\winmain.h"
#include "demo.h"
#include "game_prototype.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Win_App<Demo>(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	Win_App<GamePrototype>(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return 0;
}