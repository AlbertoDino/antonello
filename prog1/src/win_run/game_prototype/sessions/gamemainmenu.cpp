#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "../common/local.h"
#include "../ui/local.h"
#include "../model/local.h"
#include "gamemainmenu.h"


GameMainMenu::GameMainMenu()
{
	uiMainMenu = std::make_unique<UIMainMenu>();
	uiMainMenu->setOnEvent([this](eMainMenuEvent mainEvent) {
		RaisingChangeSession(eGameSession::FirstSession);
	});
}

GameMainMenu::~GameMainMenu()
{
}

void GameMainMenu::OnKey(int key, int scancode, int action, int mods)
{
}

void GameMainMenu::OnMouseScroll(double xoffset, double yoffset)
{
}

void GameMainMenu::OnWindowSizeChange(int width, int height)
{
}

void GameMainMenu::OnWindowClose()
{
}

void GameMainMenu::OnPositionCursorChange(double xpos, double ypos)
{
}

void GameMainMenu::loop(float32 elapse)
{
}

void GameMainMenu::Show()
{
	// ui objects
	render::UIContext* uiCtx = (render::UIContext*)api::getRenderingContext(api::eRenderingContext::UICxt);

	uiCtx->uiComponents.push_back(uiMainMenu.get());

}

void GameMainMenu::Hide()
{
	gApp->resetRenderingLayouts();
}
