#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "uimainmenu.h"

UIMainMenu::UIMainMenu()
{
}

void UIMainMenu::render()
{
	ImGui::Begin("Main Menu", 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	
	if (ImGui::Button("New Game") && onEvent) {
		onEvent(eMainMenuEvent::NewGame);
	}

	ImGui::End();
}

void UIMainMenu::setOnEvent(const std::function<void(eMainMenuEvent)>& callback)
{
	onEvent = callback;
}
