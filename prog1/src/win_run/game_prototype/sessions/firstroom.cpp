#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "../common/local.h"
#include "../ui/local.h"
#include "firstroom.h"

GameFirstRoom::GameFirstRoom()
{	
	sceneRoot = std::make_unique<oglElements::SceneNode>();

	camera = std::make_unique<oglElements::Camera>();
	camera->setOrigin(CVector3f(0, 0, 0));

	auto cameraRoot = camera->getCameraScene();
	cameraRoot->addChild(sceneRoot.get());
	gApp->getRoot().addChild(cameraRoot);
	
	// grid
	dbGrid = std::make_unique<sceneobjs::Grid>();
	dbGrid->add2scene();
	sceneRoot->addChild(dbGrid->getSceneNode());

	// antonello
	antonello = std::make_unique<sceneobjs::Sprite2D>();
	auto spriteRnd = antonello->render;
	spriteRnd->setTextureByFilename("assets/textures/sprite/spritesheet.png");
	spriteRnd->addAnimation("assets/textures/sprite/Run.txt", oglElements::AnimationType::Run);
	spriteRnd->addAnimation("assets/textures/sprite/Idle.txt", oglElements::AnimationType::Idle);
	spriteRnd->addAnimation("assets/textures/sprite/Jump.txt", oglElements::AnimationType::Jumps);
	spriteRnd->playAnimation(oglElements::AnimationType::Idle);
	antonello->data->name = "Antonello";
	antonello->data->positionOffset = { 0,-2,-5 };
	antonello->data->position = { 0,0,0 };
	antonello->add2scene();
	sceneRoot->addChild(antonello->getSceneNode());

	// ui
	render::UIContext* uiCtx = (render::UIContext*)api::getRenderingContext(api::eRenderingContext::UICxt);

	dbUiCameraProperties = std::make_unique<sceneobjs::UiCameraProperties>();
	dbUiCameraProperties->setCamera(camera.get());
	uiCtx->uiComponents.push_back(dbUiCameraProperties.get());
	uiCtx->uiComponents.push_back(new UIAntonelloExploreMenu());
	uiCtx->uiComponents.push_back(new sceneobjs::UIGameObjectProperties(antonello.get()));

	
}

GameFirstRoom::~GameFirstRoom()
{
	// delete all the scene objects
	if (gApp->getRoot().pFirstChild)
		delete gApp->getRoot().pFirstChild;

	// delete all the UI
	render::UIContext* uiCtx = (render::UIContext*)api::getRenderingContext(api::eRenderingContext::UICxt);

	for (auto ui_ptr : uiCtx->uiComponents)
		delete ui_ptr;
	uiCtx->uiComponents.clear();
}

void GameFirstRoom::loop(float32 elapse)
{
	camera->setProjection(gApp->gWinHandler.viewPort[2], gApp->gWinHandler.viewPort[3]);
	camera->updateViewMatrix();

	antonello->updateSpriteFrame(elapse);
}
