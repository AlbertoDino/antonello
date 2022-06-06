#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include <format>
#include "demo.h"

using namespace func;

Demo::Demo() :
	running{ true },
	camera(0),
	currentModelSelected(0)
{
	cameraNode = std::make_unique<oglElements::CameraScene>();
	cameraNode->setDebugName("camera");

	cameraAgent = std::make_unique<oglElements::Camera>();
	thirdCameraView = std::make_unique<oglElements::ThirdCameraView>();

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

	oglElements::CameraScene* cameraScene = cameraNode.get();	
	cameraAgent->setCameraNode(cameraScene);	

	cameraAgent->setOrigin(CVector3f(0, 0, 0));
	gApp->getRoot().addChild(cameraScene);
	cameraNode->addChild(sceneNode.get());

	camera = cameraAgent.get();

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
	sphere = std::make_unique<sceneobjs::GenModel>(rex::ePreBuiltModel::sphere);
	sphere->data->position = { 10,0,10 };
	sphere->add2scene(api::eRenderingContext::ShaderFlatTexture);
	sceneNode->addChild(sphere->getSceneNode());

	//-----------

	lightPosition = std::make_unique<sceneobjs::LightPosition>();
	lightPosition->add2scene();

	//-----------

	sphereNormal = std::make_unique<sceneobjs::NormalModel>();
	sphereNormal->data->name = "NormalSphere";
	sphereNormal->data->position = { 0,0,-10 };
	sphereNormal->setModel(rex::ePreBuiltModel::sphere);
	sphereNormal->setTextureByFilename("assets/textures/IceMoon.tga");
	sphereNormal->setNormalTextureByFilename("assets/textures/IceMoonBump.tga");
	sphereNormal->add2scene();

	sceneNode->addChild(sphereNormal->getSceneNode());

	//-----------
	// background

	background1 = std::make_unique<sceneobjs::GenModel>(rex::ePreBuiltModel::rectangle);
	background1->setTextureByFilename("assets/textures/s1/background1.jpg");
	background1->data->name = "background1";
	background1->data->position = { 10,0,-15 };
	background1->data->scale = { 10,10,10 };
	background1->add2scene(api::eRenderingContext::ShaderFlatTexture);
	sceneNode->addChild(background1->getSceneNode());

	//-----------

	
	floor2dTile = std::make_unique<sceneobjs::NormalModel>();
	floor2dTile->data->name = "floor2dTile";
	floor2dTile->data->position = { -1,0,0 };
	floor2dTile->setModel(rex::ePreBuiltModel::rectangle);
	
	floor2dTile->setTextureByFilename("assets/textures/176.JPG");
	floor2dTile->setNormalTextureByFilename("assets/textures/176_norm.JPG");

	floor2dTile->add2scene();

	sceneNode->addChild(floor2dTile->getSceneNode());

	//-----------

	std::vector<sceneobjs::ImageMap> textures;
	sceneobjs::ImageMap img;
	img.key = 'X';
	img.imagePath =       "assets/textures/concrete_texel.tga";
	img.imageNormalPath = "assets/textures/concrete_texel_normal.tga";
	textures.push_back(img);

	map = std::make_unique<sceneobjs::Platform2DMap>();
	map->createTexturePool(textures);
	map->generateByFile("");
	map->add2scene();

	sceneNode->addChild(map->getSceneNode());

	//-----------

	sprite = std::make_unique<sceneobjs::Sprite2D>();
	sprite->setConfigFile("assets/settings/antonello.txt");	
	sprite->loadSettingsFromFile();
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
	surface = std::make_unique<oglElements::LinearSurface>();

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
	uiCameraProperties->setCameraThirdView(thirdCameraView.get());
	uiCtx->uiComponents.push_back(uiCameraProperties.get());

	uiLightPosProperties = std::make_unique<sceneobjs::UILightPositionProperties>();
	uiLightPosProperties->setLight(lightPosition.get());
	uiCtx->uiComponents.push_back(uiLightPosProperties.get());

	uiCtx->uiComponents.push_back(new sceneobjs::UIGameObjectProperties(sprite.get()));
	uiCtx->uiComponents.push_back(new sceneobjs::UIGameObjectProperties(sphereNormal.get()));
	uiCtx->uiComponents.push_back(new sceneobjs::UIGameObjectProperties(background1.get()));

	//#####################

	cameraAgent->reset();
}

bool8 Demo::isRunning() const
{
	return running;
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


void Demo::updateUIScene(float32 elapse)
{
	uiText.list.at(0) = format("Fps %2i - elapse %.4f ", gApp->stats.fps, elapse);

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
	isActive = (key == GLFW_KEY_W);
	moveforward.Set(
		vDirection[0] * isActive,
		vDirection[1] * isActive,
		vDirection[2] * isActive);

	isActive = (key == GLFW_KEY_S);
	movebackwards.Set(
		-vDirection[0] * isActive,
		-vDirection[1] * isActive,
		-vDirection[2] * isActive);

	isActive = (key == GLFW_KEY_A);
	moveLeft.Cross(World::World_Y_Axis, vDirection);
	moveLeft.Set(
		moveLeft[0] * isActive,
		moveLeft[1] * isActive,
		moveLeft[2] * isActive);

	isActive = (key == GLFW_KEY_D);
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

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		auto* jump = sprite->createJump();
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

	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
		sprite->render->playAnimation(oglElements::AnimationType::Idle);
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
		sprite->render->playAnimation(oglElements::AnimationType::Idle);
	}

	if (key == GLFW_KEY_J && action == GLFW_PRESS)
	{
		oglElements::TaskLinearJump* jump = new oglElements::TaskLinearJump();
		jump->gameObj = sphereNormal.get();
		jump->currentJumpVector = CVector3f{ 0,1,1 } *sphereNormal->data->defaultSpeed;

		taskQueue->addTaskToQueue(jump);
		tracelog(format("Task [%i] Jump added", jump->getId()));
	}
}

void Demo::handleInput(float32 elapse)
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

	switch (glfwGetKey(window->glWindowHandler, GLFW_KEY_RIGHT))
	{
	case GLFW_PRESS:
		sprite->runRightX(elapse);
		break;

	}

	switch (glfwGetKey(window->glWindowHandler, GLFW_KEY_LEFT))
	{
	case GLFW_PRESS:
		sprite->runLefttX(elapse);
		break;
	}

	if (sprite->data->getPosition()[0] > 10)
	{
 		tracelog("3rd Camera View");
		
		thirdCameraView->setCameraScene(cameraNode.get());
		thirdCameraView->setObjectToFollow(sprite.get());

		camera = thirdCameraView.get();
	}
	else
	{
		tracelog("Camera Free node");
		cameraAgent->setCameraNode(cameraNode.get());
		camera = cameraAgent.get();
	}

	inputRotation *= rotationActive;
}


void Demo::loop(float32 elapse)
{
	handleInput(elapse);

	if (camera) {
		camera->setProjection(window->width, window->height);
		camera->move(inputMovement, elapse);
		camera->rotate(inputRotation, elapse);
		camera->updateViewMatrix();
	}

	taskExecuter.loop(elapse);

	for (auto* obj : models) {
		obj->updateMatrixes();
	}

	map->updateMatrixes();
	sprite->updateSpriteFrame(elapse);

	floor2dTile->updateMatrixes();
	sphere->updateMatrixes();

	light->update(cameraAgent->getPosition());
	lightPosition->update(cameraAgent->getPosition());

	sphereNormal->updateMatrixes();
	background1->updateMatrixes();

	updateUIScene(elapse);

	inputMovement.Set(0);
	inputRotation.Set(0);

	oglElements::checkForOpenglErrors();
}


