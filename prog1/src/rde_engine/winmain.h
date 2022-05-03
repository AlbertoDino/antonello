#pragma once

#include <rde_common/lib.h>
#include "console.h"
#include "application.h"

EXTERN_ Application* gApp;


INLINE_ void Win_Init(HINSTANCE hInstance, LPSTR lpCmdLine)
{
	func::World::World_X_Axis.Set(1.0f, 0.0f, 0.0f);
	func::World::World_Y_Axis.Set(0.0f, 1.0f, 0.0f);
	func::World::World_Z_Axis.Set(0.0f, 0.0f, 1.0f);

	gApp = new Application(hInstance);

	oglElements::WinObj console;
	console.top = 50;
	console.left = 10;
	console.width = 800;
	console.height = 500;

	gConsole = new win::Console(console);
	gConsole-> init(hInstance);

	tracelog("console created");

}

template<class GAME>
INLINE_ void Win_Run(int nShowCmd)
{
	MSG msg;
	GAME* game = new GAME();


	gApp->init();

	game->init();

#if SET_THREAD_AFFINITY == 1
	// give the main thread an affinity for the first cpu
	SetThreadAffinityMask(GetCurrentThread(), 1);
#endif

	while (game->isRunning())
	{

		float32 elapse = gApp->timer.getDiffElapsedSeconds();

		game->loop(elapse);
		gApp->render();

		gApp->calculateStats(elapse);
	}

	gApp->end();
}


template<class GAME>
INLINE_ int		Win_App(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int nFrameContexts = 1, const char8* cDefaultPath = 0)
{
	Win_Init(hInstance, lpCmdLine);
	Win_Run<GAME>(nCmdShow);

	if (gConsole) {
		delete gConsole;
	}
	return 0;
}