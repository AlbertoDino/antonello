#pragma once
#include <functional>

enum eMainMenuEvent : int32 {
	NewGame
};

class UIMainMenu : public oglElements::IUIComponent {
public:
	UIMainMenu();

	void render();

	void setOnEvent(const std::function<void(eMainMenuEvent)>& callback);

private:
	std::function<void(eMainMenuEvent)> onEvent;
};