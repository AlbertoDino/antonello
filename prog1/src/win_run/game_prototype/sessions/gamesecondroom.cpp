#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "../common/local.h"
#include "../ui/local.h"
#include "../model/local.h"
#include "gamesecondroom.h"

GameSecondRoom::GameSecondRoom()
{
	glWindowHandler = gApp->gWinHandler.glWindowHandler;

	sceneRoot = std::make_unique<oglElements::SceneNode>();
	cameraNode = std::make_unique<oglElements::CameraScene>();

	camera = std::make_unique<oglElements::Camera>();
	camera->setCameraNode(cameraNode.get());
	camera->setOrigin(CVector3f(0, 0, 0));

	auto cameraRoot = camera->getCameraScene();
	cameraRoot->addChild(sceneRoot.get());

	interaction = std::make_unique<FixedFrameInteraction>();

	//task executer
	taskQueue = std::make_unique<oglElements::TaskQueue>();
	taskExecuter.init(taskQueue.get());
	taskExecuter.setInteraction(interaction.get());

	// grid
	dbGrid = std::make_unique<sceneobjs::Grid>();
	sceneRoot->addChild(dbGrid->getSceneNode());

	// background
	background1 = std::make_unique<sceneobjs::GenModel>(rex::ePreBuiltModel::rectangle);
	background1->setTextureByFilename("assets/textures/s1/background2.jpg");
	background1->setConfigFile("assets/settings/background2-game1.txt");
	background1->loadSettingsFromFile();
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
	sceneRoot->addChild(antonello->getSceneNode());

	// world settings

	interaction->surface.setDefaultHeight(0);
	interaction->frameBox[0] = -1.6; // this depends how close antonello is to the camera 
	interaction->frameBox[1] = +1.6; // this depends how close antonello is to the camera 

}

GameSecondRoom::~GameSecondRoom()
{
}

void GameSecondRoom::OnKey(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		antonello->render->playAnimation(oglElements::AnimationType::Idle);
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		antonello->render->playAnimation(oglElements::AnimationType::Idle);
	}
}

void GameSecondRoom::OnMouseScroll(double xoffset, double yoffset)
{
}

void GameSecondRoom::OnWindowSizeChange(int width, int height)
{
}

void GameSecondRoom::OnWindowClose()
{
}

void GameSecondRoom::OnPositionCursorChange(double xpos, double ypos)
{
}

void GameSecondRoom::loop(float32 elapse)
{
	handleInput(elapse);
	camera->setProjection(gApp->gWinHandler.viewPort[2], gApp->gWinHandler.viewPort[3]);
	camera->updateViewMatrix();

	antonello->updateSpriteFrame(elapse);
	background1->updateMatrixes();

	taskExecuter.loop(elapse);
}

void GameSecondRoom::handleInput(float32 elapse)
{
	switch (glfwGetKey(glWindowHandler, GLFW_KEY_RIGHT))
	{
	case GLFW_PRESS:
		taskQueue->addTaskToQueue(
			antonello->createRightMovement()
		);
		break;
	}

	switch (glfwGetKey(glWindowHandler, GLFW_KEY_LEFT))
	{
	case GLFW_PRESS:
		taskQueue->addTaskToQueue(
			antonello->createLeftMovement()
		);
		break;
	}

	switch (glfwGetKey(glWindowHandler, GLFW_KEY_SPACE))
	{
	case GLFW_PRESS:
		taskQueue->addTaskToQueue(
			antonello->createJump()
		);
		break;
	}

	if (antonello->data->position[0] <= interaction->frameBox[0]) {
		RaisingChangeSession(eGameSession::FirstSession);
	}
}

void GameSecondRoom::Show()
{
	auto cameraRoot = camera->getCameraScene();
	gApp->getRoot().addChild(cameraRoot);

	gApp->resetRenderingLayouts();

	// scene objects	
	dbGrid->add2scene();
	background1->add2scene(api::eRenderingContext::ShaderFlatTexture);
	antonello->add2scene();

	// ui objects
	render::UIContext* uiCtx = (render::UIContext*)api::getRenderingContext(api::eRenderingContext::UICxt);
	uiCtx->uiComponents.push_back(new sceneobjs::UIGameObjectProperties(background1.get()));
}

void GameSecondRoom::Hide()
{
	auto cameraRoot = camera->getCameraScene();
	gApp->getRoot().removeChild(cameraRoot);
	gApp->resetRenderingLayouts();
}
