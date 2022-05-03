#pragma once
#include "game_prototype/common/local.h"


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

private:
	bool8 running;
	IGameSession* activeSession;
};