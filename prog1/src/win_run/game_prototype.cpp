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

GamePrototype::GamePrototype() : running(true), activeSession(0)
{
	gApp->gWinHandler.width = 1600;
	gApp->gWinHandler.height = 1024;

	int32 gameViewHeight = getPerCent(gApp->gWinHandler.height,75);

	gApp->gWinHandler.viewPort[0] = 0;
	gApp->gWinHandler.viewPort[1] = gApp->gWinHandler.height- gameViewHeight;
	gApp->gWinHandler.viewPort[2] = gApp->gWinHandler.width;
	gApp->gWinHandler.viewPort[3] = gameViewHeight;
	gApp->gWinHandler.isFullScreen = false;
	gApp->gWinHandler.title = "GamePrototype";
	gApp->gWinHandler.user_pointer = this;

}

void GamePrototype::init()
{
	activeSession = new GameFirstRoom();
}

void GamePrototype::loop(float32 elapse)
{
	activeSession->loop(elapse);
}

bool8 GamePrototype::isRunning() const
{
	return running;
}

void GamePrototype::OnKey(int key, int scancode, int action, int mods)
{
}

void GamePrototype::OnMouseScroll(double xoffset, double yoffset)
{
}

void GamePrototype::OnWindowSizeChange(int width, int height)
{
	int32 gameViewHeight = getPerCent(height, 75);
	
	gApp->gWinHandler.viewPort[0] = 0;
	gApp->gWinHandler.viewPort[1] = height - gameViewHeight;
	gApp->gWinHandler.viewPort[2] = width;
	gApp->gWinHandler.viewPort[3] = gameViewHeight;
}

void GamePrototype::OnWindowClose()
{
	running = false;
}

void GamePrototype::OnPositionCursorChange(double xpos, double ypos)
{
}

