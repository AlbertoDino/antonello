#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "uiantonelloexploremenu.h"

UIAntonelloExploreMenu::UIAntonelloExploreMenu()
{
}

void UIAntonelloExploreMenu::render()
{

	ImGui::SetWindowPos({ 20,800 });
	
	ImGui::Begin("Game",0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);	
	ImGui::Button("Take");
	ImGui::Button("Analyze");
	ImGui::Button("Use");
	ImGui::End();
}
