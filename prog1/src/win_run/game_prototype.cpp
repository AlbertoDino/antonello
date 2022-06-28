#pragma once
#include <3rdparty/lib.h>
#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "game_prototype/common/local.h"
#include "game_prototype/sessions/local.h"
#include "game_prototype.h"



int32 getPerCent(int32 v, float32 perCent) {

	float32 fac = 100.0f / perCent;
	return static_cast<int32>(std::floor(v / fac));
}

GamePrototype::GamePrototype() : 
	running(true), 
	activeSession(0),
	nextSession(0)
{
	gApp->gWinHandler.width = 1600;
	gApp->gWinHandler.height = 1024;

	int32 gameViewHeight = getPerCent(gApp->gWinHandler.height, 75);

	gApp->gWinHandler.viewPort[0] = 0;
	gApp->gWinHandler.viewPort[1] = gApp->gWinHandler.height - gameViewHeight;
	gApp->gWinHandler.viewPort[2] = gApp->gWinHandler.width;
	gApp->gWinHandler.viewPort[3] = gameViewHeight;
	gApp->gWinHandler.isFullScreen = false;
	gApp->gWinHandler.title = "GamePrototype";
	gApp->gWinHandler.user_pointer = this;



}

GamePrototype::~GamePrototype()
{
}

void GamePrototype::init()
{
	// Game sessions
	gameMainMenu = std::make_unique<GameMainMenu>();
	gameFirst = std::make_unique<GameFirstRoom>();
	gameSecond = std::make_unique<GameSecondRoom>();

	gameMainMenu->setRaiseSessionCallback([this](eGameSession session) { OnChangeSession(session); });
	gameFirst->setRaiseSessionCallback([this](eGameSession session) { OnChangeSession(session); });
	gameSecond->setRaiseSessionCallback([this](eGameSession session) { OnChangeSession(session); });

	//
	OnChangeSession(eGameSession::MainMenu);
}

void GamePrototype::OnChangeSession(eGameSession session)
{
	switch (session)
	{
	case MainMenu:
		nextSession = gameMainMenu.get();
		break;
	case FirstSession:
		nextSession = gameFirst.get();
		break;
	case SecondSession:
		nextSession = gameSecond.get();
		break;
	default:
		tracelog(format("Error! session [%i] not found",session));
		nextSession = gameMainMenu.get();
		break;
	}
}



void GamePrototype::loop(float32 elapse)
{
	if (nextSession) {
		if (activeSession)
			activeSession->Hide();
		activeSession = nextSession;
		activeSession->Show();
		nextSession = 0;
	}

	if(activeSession)
		activeSession->loop(elapse);
}

bool8 GamePrototype::isRunning() const
{
	return running;
}

void GamePrototype::OnKey(int key, int scancode, int action, int mods)
{
	activeSession->OnKey(key, scancode, action, mods);
}

void GamePrototype::OnMouseScroll(double xoffset, double yoffset)
{
}

void GamePrototype::OnWindowSizeChange(int width, int height)
{
	auto main = dynamic_cast<GameMainMenu*>(activeSession);
	if (main) {
		menuViewPort(width, height);
	}
	else {
		gameViewPort(width, height);
	}
}

void GamePrototype::OnWindowClose()
{
	running = false;
}

void GamePrototype::OnPositionCursorChange(double xpos, double ypos)
{
}

void GamePrototype::gameViewPort(int width, int height)
{
	int32 gameViewHeight = getPerCent(height, 75);

	gApp->gWinHandler.viewPort[0] = 0;
	gApp->gWinHandler.viewPort[1] = height - gameViewHeight;
	gApp->gWinHandler.viewPort[2] = width;
	gApp->gWinHandler.viewPort[3] = gameViewHeight;
}

void GamePrototype::menuViewPort(int width, int height)
{
	gApp->gWinHandler.viewPort[0] = 0;
	gApp->gWinHandler.viewPort[1] = 0;
	gApp->gWinHandler.viewPort[2] = width;
	gApp->gWinHandler.viewPort[3] = height;
}

