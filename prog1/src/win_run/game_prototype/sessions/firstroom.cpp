#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "../common/local.h"
#include "../ui/local.h"
#include "firstroom.h"

GameFirstRoom::GameFirstRoom()
{	
	sceneRoot = std::make_unique<oglElements::SceneNode>();

	cameraNode = std::make_unique<oglElements::CameraScene>();

	camera = std::make_unique<oglElements::Camera>();
	camera->setCameraNode(cameraNode.get());
	camera->setOrigin(CVector3f(0, 0, 0));

	auto cameraRoot = camera->getCameraScene();
	cameraRoot->addChild(sceneRoot.get());
	gApp->getRoot().addChild(cameraRoot);
	
	// grid
	dbGrid = std::make_unique<sceneobjs::Grid>();
	dbGrid->add2scene();
	sceneRoot->addChild(dbGrid->getSceneNode());

	

	// background
	background1 = std::make_unique<sceneobjs::GenModel>(rex::ePreBuiltModel::rectangle);
	background1->setTextureByFilename("assets/textures/s1/background1.jpg");
	background1->setConfigFile("assets/settings/antonello-game1.txt");
	background1->data->name = "background1";
	background1->data->position = { 0,0,-10 };
	background1->add2scene(api::eRenderingContext::ShaderFlatTexture);
	sceneRoot->addChild(background1->getSceneNode());

	// antonello [last for transparency]
	antonello = std::make_unique<sceneobjs::Sprite2D>();
	antonello->setConfigFile("assets/settings/antonello-game1.txt");
	antonello->loadSettingsFromFile();
	auto spriteRnd = antonello->render;
	spriteRnd->setTextureByFilename("assets/textures/sprite/spritesheet.png");
	spriteRnd->addAnimation("assets/textures/sprite/Run.txt", oglElements::AnimationType::Run);
	spriteRnd->addAnimation("assets/textures/sprite/Idle.txt", oglElements::AnimationType::Idle);
	spriteRnd->addAnimation("assets/textures/sprite/Jump.txt", oglElements::AnimationType::Jumps);
	spriteRnd->playAnimation(oglElements::AnimationType::Idle);
	antonello->data->name = "Antonello";
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
	uiCtx->uiComponents.push_back(new sceneobjs::UIGameObjectProperties(background1.get()));

	
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
	background1->updateMatrixes();
	
}
