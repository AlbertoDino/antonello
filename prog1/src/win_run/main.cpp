#include "..\rde_engine\winmain.h"
#include "demo.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Win_App<Demo>(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return 0;
}