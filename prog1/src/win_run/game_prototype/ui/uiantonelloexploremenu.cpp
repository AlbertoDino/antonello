#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "uiantonelloexploremenu.h"

UIAntonelloExploreMenu::UIAntonelloExploreMenu()
{
}

void UIAntonelloExploreMenu::render()
{
	//

	float32 posX = 20;
	float32 posY = (int)gApp->gWinHandler.viewPort[3] + (int)20;
	
	ImGui::Begin("Game",0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);	
	ImGui::SetWindowPos({ posX , posY });
	ImGui::SetWindowSize({ 600, 120 });

	ImGui::Button("Take");
	ImGui::Button("Analyze");
	ImGui::Button("Use");
	ImGui::End();
}
