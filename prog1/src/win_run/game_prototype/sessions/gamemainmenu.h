#pragma once
#include "../ui/local.h"

class GameMainMenu : public IGameSession {
public:
	GameMainMenu();
	~GameMainMenu();

	virtual void OnKey(int key, int scancode, int action, int mods);
	virtual void OnMouseScroll(double xoffset, double yoffset);
	virtual void OnWindowSizeChange(int width, int height);
	virtual void OnWindowClose();
	virtual void OnPositionCursorChange(double xpos, double ypos);
	virtual void loop(float32 elapse);

	virtual void Show();
	virtual void Hide();

private:
	GLFWwindow* glWindowHandler;
	
	std::unique_ptr<UIMainMenu> uiMainMenu;
};