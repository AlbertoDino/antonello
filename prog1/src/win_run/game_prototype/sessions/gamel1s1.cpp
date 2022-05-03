#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "../common/local.h"
#include "gamel1s1.h"

GameL1S1::GameL1S1()
{	
	sceneRoot = std::make_unique<oglElements::SceneNode>();

	camera = std::make_unique<oglElements::Camera>();
	camera->setOrigin(CVector3f(0, 0, 0));

	auto cameraRoot = camera->getCameraScene();
	cameraRoot->addChild(sceneRoot.get());
	gApp->getRoot().addChild(cameraRoot);
	
	// grid
	grid = std::make_unique<sceneobjs::Grid>();
	grid->add2scene();
	sceneRoot->addChild(grid->getSceneNode());

	render::UIContext* uiCtx = (render::UIContext*)api::getRenderingContext(api::eRenderingContext::UICxt);

	uiCameraProperties = std::make_unique<sceneobjs::UiCameraProperties>();
	uiCameraProperties->setCamera(camera.get());
	uiCtx->uiComponents.push_back(uiCameraProperties.get());
}

GameL1S1::~GameL1S1()
{
}

void GameL1S1::loop(float32 elapse)
{
	camera->setProjection(gApp->gWinHandler.viewPort[2], gApp->gWinHandler.viewPort[3]);
	camera->updateViewMatrix();
}
