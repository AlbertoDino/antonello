#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include <format>
#include "demo.h"

using namespace func;

Demo::Demo() :
	running{ true },
	currentModelSelected(0)
{
	cameraAgent = std::make_unique<oglElements::Camera>();
	sceneNode = std::make_unique<oglElements::SceneNode>();
	sceneNode->setDebugName("sceneNode");
	
	lastRotation.Set(0);

	gApp->gWinHandler.width = 1600;
	gApp->gWinHandler.height = 1024;
	gApp->gWinHandler.viewPort[2] = 1600;
	gApp->gWinHandler.viewPort[3] = 1024;
	gApp->gWinHandler.isFullScreen = false;
	gApp->gWinHandler.title = "Demo";
	gApp->gWinHandler.user_pointer = this;
}

Demo::~Demo()
{

}


void Demo::init()
{
	window = &(gApp->gWinHandler);

	oglElements::CameraScene* cameraNode = cameraAgent->getCameraScene();
	cameraNode->setDebugName("camera");
	cameraAgent->setOrigin(CVector3f(0, 0, 0));

	gApp->getRoot().addChild(cameraNode);	
	cameraNode->addChild(sceneNode.get());

	//-----------
	grid1 = std::make_unique<sceneobjs::Grid>();
	grid1->add2scene();
	sceneNode->addChild(grid1->getSceneNode());
	//-----------
	light = std::make_unique<sceneobjs::Light>();
	light->color.Set(colors::White[0], colors::White[1], colors::White[2]);
	light->direction.Set(-150, 80, 3);
	light->add2scene();
	sceneNode->addChild(light->getSceneNode());
	//-----------
	pickingCtx = api::getPixelReadContext();
	pickingCtx->setOnSelected([this](uint32 id) { onModelSelected(id); uiModelProperties->setModelSelected(currentModelSelected); });

	//-----------
	oglElements::DrawElementTextured* sphererender = new oglElements::DrawElementTextured();
	sphererender->vertexObject = rex::Sphere::getModel(1.0f,36,18);
	sphererender->textureObject = api::getDefaultTexture();
	sphere = std::make_unique<sceneobjs::GenModel>(sphererender);
	sphere->data->position = { 10,10,10 };
	sphere->add2scene(api::eRenderingContext::ShaderFlatTexture);
	sceneNode->addChild(sphere->getSceneNode());

	//-----------

	lightPosition = std::make_unique<sceneobjs::LightPosition>();
	lightPosition->add2scene();

	sphereNormal = std::make_unique<sceneobjs::NormalModel>();
	sphereNormal->data->name = "NormalSphere";
	sphereNormal->data->position = { 0,0,-10 };
	sphereNormal->setModel(rex::ePreBuiltModel::sphere);
	sphereNormal->setTextureByFilename      ("assets/textures/IceMoon.tga");
	sphereNormal->setNormalTextureByFilename("assets/textures/IceMoonBump.tga");
	sphereNormal->add2scene();

	sceneNode->addChild(sphereNormal->getSceneNode());

	//-----------

	sphererender->textureObject = sphereNormal->getRendering()->textureNormal;

	sprite = std::make_unique<sceneobjs::Sprite2D>();
	sprite->data->defaultSpeed = 0.350;
	auto spriteRnd = sprite->render;
	spriteRnd->setTextureByFilename("assets/textures/sprite/spritesheet.png");
	spriteRnd->addAnimation("assets/textures/sprite/Run.txt", oglElements::AnimationType::Run);
	spriteRnd->addAnimation("assets/textures/sprite/Idle.txt", oglElements::AnimationType::Idle);
	spriteRnd->addAnimation("assets/textures/sprite/Jump.txt", oglElements::AnimationType::Jumps);

	spriteRnd->playAnimation(oglElements::AnimationType::Idle);

	sprite->add2scene();
	sceneNode->addChild(sprite->getSceneNode());

	//#####################

	taskQueue = std::make_unique<oglElements::TaskQueue>();
	surface = std::make_unique<win::LinearSurface>();

	taskExecuter.init(taskQueue.get());	
	taskExecuter.setSurface(surface.get());


	//#####################
	// ui
	render::UIContext* uiCtx = (render::UIContext*)api::getRenderingContext(api::eRenderingContext::UICxt);
	uiText.list.push_back("<place_holder>");
	uiText.list.push_back("press v : reset camera");
	uiText.list.push_back("press F1 : turn campera 90 dg");
	uiText.list.push_back("press F2 : turn campera -90 dg");
	uiText.list.push_back("press J : for jump");

	uiModelProperties = std::make_unique<sceneobjs::UiModelProperties>();
	uiModelProperties->set_mesh_load_callback([this](std::string filepath) { addObjectFromFile(filepath); });
	uiModelProperties->set_model_selected_callback([this](uint32 id) { onModelSelected(id); });
	uiCtx->uiComponents.push_back(uiModelProperties.get());

	uiLightProperties = std::make_unique<sceneobjs::UILightProperties>();
	uiLightProperties->setLight(light.get());
	uiCtx->uiComponents.push_back(uiLightProperties.get());

	uiCameraProperties = std::make_unique<sceneobjs::UiCameraProperties>();
	uiCameraProperties->setTextList(&uiText);
	uiCameraProperties->setCamera(cameraAgent.get());
	uiCtx->uiComponents.push_back(uiCameraProperties.get());

	uiLightPosProperties = std::make_unique<sceneobjs::UILightPositionProperties>();
	uiLightPosProperties->setLight(lightPosition.get());
	uiCtx->uiComponents.push_back(uiLightPosProperties.get());

	uiCtx->uiComponents.push_back(new sceneobjs::UIGameObjectProperties(sprite.get()));

	uiCtx->uiComponents.push_back(new sceneobjs::UIGameObjectProperties(sphereNormal.get()));

	//#####################

	cameraAgent->reset();
}

bool8 Demo::isRunning() const
{
	return running;
}

/*
The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
*/
void Demo::OnKey(int key, int scancode, int action, int mods)
{
	CVector3f moveforward;
	CVector3f movebackwards;
	CVector3f moveLeft;
	CVector3f moveRight;

	CVector3f vDirection = cameraAgent->getDirection();

	//tracelog(format("Key %2i, scancode %2i, action %2i, mods %2i", key, scancode, action, mods));

	// Keyboard
	bool8 isActive;
	isActive = (key == GLFW_KEY_W /* && (action == GLFW_PRESS || action == GLFW_REPEAT)*/);
	moveforward.Set(
		vDirection[0] * isActive,
		vDirection[1] * isActive,
		vDirection[2] * isActive);

	isActive = (key == GLFW_KEY_S /* && (action == GLFW_PRESS || action == GLFW_REPEAT) */);
	movebackwards.Set(
		-vDirection[0] * isActive,
		-vDirection[1] * isActive,
		-vDirection[2] * isActive);

	isActive = (key == GLFW_KEY_A /* && (action == GLFW_PRESS || action == GLFW_REPEAT) */);
	moveLeft.Cross(World::World_Y_Axis, vDirection);
	moveLeft.Set(
		moveLeft[0] * isActive,
		moveLeft[1] * isActive,
		moveLeft[2] * isActive);

	isActive = (key == GLFW_KEY_D /* && (action == GLFW_PRESS || action == GLFW_REPEAT) */);
	moveRight.Cross(World::World_Y_Axis, vDirection);
	moveRight.Set(
		-moveRight[0] * isActive,
		-moveRight[1] * isActive,
		-moveRight[2] * isActive);

	inputMovement += moveforward;
	inputMovement += movebackwards;
	inputMovement += moveLeft;
	inputMovement += moveRight;

	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		glfwSetCursorPos(window->glWindowHandler, window->width / 2, window->height / 2);
		cameraAgent->reset();
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		cameraAgent->turn90();
	}

	if (key == GLFW_KEY_F2 && action == GLFW_PRESS)
	{
		cameraAgent->turnless90();
	}

	if (key == GLFW_KEY_SPACE)
	{
		win::TaskLinearJump* jump = new win::TaskLinearJump();
		jump->gameObj = sprite.get();
		
		int32 direction2d = sprite->isFacingLeft() ? -1 : 1;

		jump->currentJumpVector = CVector3f { 0.25f*(direction2d),1.5,0 } *sprite->data->defaultSpeed;
		jump->onComplete(
			[this](oglElements::Task* t) {
				auto sprite = (sceneobjs::Sprite2D*)t->gameObj;
				sprite->render->playAnimation(oglElements::AnimationType::Idle);
			}
		);
		taskQueue->addTaskToQueue(jump);
		tracelog(format("Task [%i] Jump added", jump->getId()));
		sprite->render->playAnimation(oglElements::AnimationType::Jumps);

	}

	if (key == GLFW_KEY_LEFT_SHIFT)
	{
		sprite->render->playAnimation(oglElements::AnimationType::Run);
	}

	if (key == GLFW_KEY_X)
	{
		sprite->render->playAnimation(oglElements::AnimationType::Idle);
	}

	// GLFW_KEY_RIGHT
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		tracelog("Sprite turning right");

		if (!sprite->isFacingRight()) {
			sprite->data->orientation.Rotate(CVector3f{ 180,0,0 }, 1);
		}

		sprite->updateMatrixes();
		
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
	{
		tracelog("Sprite running right");
		CVector3f vDirection = sprite->data->direction;

		oglElements::FreePhysic physic(sprite.get());

		CVector3f moveRight;
		moveRight.Cross(World::World_Y_Axis, vDirection );

		physic.move(moveRight, 0.5);
		sprite->updateMatrixes();

		sprite->render->playAnimation(oglElements::AnimationType::Run);
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		sprite->render->playAnimation(oglElements::AnimationType::Idle);
	}


	// GLFW_KEY_LEFT

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS )
	{
		tracelog("Sprite turning left");

		if (!sprite->isFacingLeft()) {
			sprite->data->orientation.Rotate(CVector3f{ -180,0,0 }, 1);
		}

		sprite->updateMatrixes();
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
	{
		tracelog("Sprite running left");
		CVector3f vDirection = sprite->data->direction;

		oglElements::FreePhysic physic(sprite.get());

		CVector3f moveLeft;
		moveLeft.Cross(World::World_Y_Axis, vDirection);

		physic.move(moveLeft, 0.5);
		sprite->updateMatrixes();

		sprite->render->playAnimation(oglElements::AnimationType::Run);
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		sprite->render->playAnimation(oglElements::AnimationType::Idle);
	}

	if (key == GLFW_KEY_J && action == GLFW_PRESS)
	{
		win::TaskLinearJump* jump = new win::TaskLinearJump();
		jump->gameObj = sphereNormal.get();
		jump->currentJumpVector = CVector3f{ 0,1,1 } * sphereNormal->data->defaultSpeed;

		taskQueue->addTaskToQueue(jump);
		tracelog(format("Task [%i] Jump added", jump->getId()));
	}
}

void Demo::OnMouseScroll(double xoffset, double yoffset)
{
}

void Demo::OnWindowSizeChange(int width, int height)
{
	gApp->gWinHandler.viewPort[2] = width;
	gApp->gWinHandler.viewPort[3] = height;
}

void Demo::OnWindowClose()
{
	running = false;
}

void Demo::OnPositionCursorChange(double xposd, double yposd)
{
	float32 xpos = static_cast<float32>(xposd);
	float32 ypos = static_cast<float32>(yposd);

	//tracelog(format("Mouse Pos [%2.2f,%2.2f]", xpos, ypos));

	float32 xOffset = xpos - lastRotation[0];
	float32 yOffset = lastRotation[1] - ypos;

	lastRotation[0] = xpos;
	lastRotation[1] = ypos;

	inputRotation.Set(xOffset, -yOffset, 0);

	Coord2i mousePos;
	mousePos[0] = static_cast<int32>(xposd);
	mousePos[1] = static_cast<int32>(yposd);

	pickingCtx->setSelectionByMousePosition(mousePos);
}


void Demo::updateUIScene()
{
	uiText.list.at(0) = format("Fps %2i ", gApp->stats.fps);

	uiModelProperties->setModelList(models);
}

void Demo::addObjectFromFile(std::string filepath)
{
	oglElements::Mesh mesh;
	if (!mesh.loadFromFile(filepath)) {
		throwError("Cannot load mesh from file");
		return;
	}

	sceneobjs::Model* obj = new sceneobjs::Model();
	vSet(obj->color, colors::Red);
	obj->data->name = filepath.substr(filepath.find_last_of("/\\") + 1);
	obj->data->position.Set(10 * models.size(), 2, 5 * models.size());
	mesh.create((oglElements::DrawElementTextured*)obj->refRender);

	sceneNode->addChild(obj->getSceneNode());
	obj->add2SceneWithLightShader();
	models.push_back(obj);

	oglElements::DrawArrayObject* draw = new oglElements::DrawArrayObject();
	draw->vertexObject = rex::Cube::getModel();
	sceneobjs::Model* AABB = new sceneobjs::Model(draw);
	ColorFromUID(obj->data->id, AABB->color);
	AABB->data->name = "AABB";
	AABB->add2SceneWithFlatShader();
	AABB->add2PickingLayer();
	obj->getSceneNode()->addChild(AABB->getSceneNode());

	tracelog(format("Model [%s] loaded with id [%i]", obj->data->name.c_str(), obj->data->id));

}

void Demo::onModelSelected(uint32 id)
{
	tracelog(format("onModelSelected [%i]", id));
	currentModelSelected = 0;
	for (auto model : models) {
		if (model->data->id == id) {
			currentModelSelected = model;
			tracelog(format("Model [%s] [%i] has been selected", currentModelSelected->data->name.c_str(), currentModelSelected->data->id));
		}
	}
}

void Demo::handleInput()
{
	static float32 rotationActive = 1.0f;
	win::eMouseButton mouseButton = win::getMousePressedButton(window);

	if (mouseButton == win::eMouseButton::Right)
	{
		rotationActive = func::IsEqual(rotationActive, 0.0) ? 1.0f : 0.0f;
	}

	if (mouseButton == win::eMouseButton::Left)
	{
		pickingCtx->evaluate();
	}

	inputRotation *= rotationActive;
}


void Demo::loop(float32 elapse)
{
	handleInput();

	cameraAgent->setProjection(window->width, window->height);
	cameraAgent->move(inputMovement, elapse);
	cameraAgent->rotate(inputRotation, elapse);
	cameraAgent->updateViewMatrix();


	taskExecuter.loop(elapse);

	for (auto* obj : models) {
		obj->updateMatrixes();
	}

	sprite->updateSpriteFrame(elapse);
	sphere->updateMatrixes();

	light->update(cameraAgent->getPosition());
	lightPosition->update(cameraAgent->getPosition());

	sphereNormal->updateMatrixes();

	updateUIScene();

	inputMovement.Set(0);
	inputRotation.Set(0);

	oglElements::checkForOpenglErrors();
}


