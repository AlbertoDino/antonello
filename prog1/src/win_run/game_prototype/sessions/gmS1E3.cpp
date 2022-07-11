#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "../common/local.h"
#include "../ui/local.h"
#include "../model/local.h"
#include "gmS1E3.h"

GmS1E3::GmS1E3()
{
	glWindowHandler = gApp->gWinHandler.glWindowHandler;

	sceneRoot = std::make_unique<oglElements::SceneNode>();
	cameraNode = std::make_unique<oglElements::CameraScene>();
	camera = std::make_unique<oglElements::ThirdCameraView>();

	camera->setCameraScene(cameraNode.get());
	cameraNode->addChild(sceneRoot.get());
}

GmS1E3::~GmS1E3()
{
}

void GmS1E3::OnKey(int key, int scancode, int action, int mods)
{
}

void GmS1E3::OnMouseScroll(double xoffset, double yoffset)
{
}

void GmS1E3::OnWindowSizeChange(int width, int height)
{
}

void GmS1E3::OnWindowClose()
{
}

void GmS1E3::OnPositionCursorChange(double xpos, double ypos)
{
}

void GmS1E3::loop(float32 elapse)
{
}

void GmS1E3::Show()
{
}

void GmS1E3::Hide()
{
}

void GmS1E3::handleInput(float32 elapse)
{
}
