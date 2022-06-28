#pragma once
#include "game_prototype/common/local.h"
#include "game_prototype/sessions/local.h"


enum eGameSessionStatus : int32 {

};

class GamePrototype  :  public render::WinEventHandler {
public:
	GamePrototype();
	~GamePrototype();

	void init();
	void loop(float32 elapse);

	bool8 isRunning() const;

	virtual void OnKey(int key, int scancode, int action, int mods);
	virtual void OnMouseScroll(double xoffset, double yoffset);
	virtual void OnWindowSizeChange(int width, int height);
	virtual void OnWindowClose();
	virtual void OnPositionCursorChange(double xpos, double ypos);

	void gameViewPort(int width, int height);
	void menuViewPort(int width, int height);


	void OnChangeSession(eGameSession session);

private:
	bool8 running;
	IGameSession* activeSession,*nextSession;

	//Sessions
	std::unique_ptr<GameMainMenu> gameMainMenu;
	std::unique_ptr<GameFirstRoom> gameFirst;
	std::unique_ptr<GameSecondRoom> gameSecond;

};