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
	sceneNode	= std::make_unique<oglElements::SceneNode>();
	grid1		= std::make_unique<sceneobjs::Grid>();
	light		= std::make_unique<sceneobjs::Light>();

	lastRotation.Set(0);	
}

Demo::~Demo()
{

}

void Demo::init(oglElements::WinObj* gWininstance)
{
	window = gWininstance;
	
	render::UIContext* uiCtx = (render::UIContext*)api::getRenderingContext(api::eRenderingContext::UICxt);
	ui.dialogName = "stats";
	ui.textList.push_back("<place_holder>");
	ui.textList.push_back("<place_holder>");
	ui.textList.push_back("<place_holder>");
	ui.textList.push_back("<place_holder>");
	ui.textList.push_back("press v : reset camera");
	ui.textList.push_back("press A : turn campera 90 dg");
	ui.textList.push_back("press D : turn campera -90 dg");
	
	uiModelProperties = std::make_unique<sceneobjs::UiModelProperties>();
	uiModelProperties->set_mesh_load_callback([this](std::string filepath) { addObjectFromFile(filepath); });
	uiModelProperties->set_model_selected_callback([this](uint32 id) { onModelSelected(id); });
	ui.uiComponents.push_back(uiModelProperties.get());	

	uiLightProperties = std::make_unique<sceneobjs::UILightProperties>();
	uiLightProperties->setLight(light.get());
	ui.uiComponents.push_back(uiLightProperties.get());

	uiCtx->render(&ui);

	oglElements::CameraScene* cameraNode = cameraAgent->getCameraScene();
	cameraNode->setDebugName("camera");
	cameraAgent->setOrigin(CVector3f(0, 0, 0));
	cameraAgent->setSpeed(150);
	cameraAgent->setSpeedRotation(20);

	// Create Grid
	oglElements::ArrayMesh gridCreate;
	float32 lenght = 20.0f;
	float32 height = 0.55f;
	for (float32 x = -lenght; x <= lenght; x += 0.5) {
		gridCreate.vertex3f(x, -height, lenght);
		gridCreate.vertex3f(x, -height, -lenght);
		gridCreate.vertex3f(lenght, -height, x);
		gridCreate.vertex3f(-lenght, -height, x);
	}

	gridCreate.create((oglElements::DrawArrayObject*)grid1->pRender);
	vSet(grid1->color, colors::Green);
	grid1->add2scene();

	light->color.Set(colors::White[0], colors::White[1], colors::White[2]);
	light->direction.Set(-150, 80, 3);
	light->add2scene();
	
	gApp->getRoot().addChild(cameraNode);
	
	sceneNode->setDebugName("sceneNode");
	cameraNode->addChild(sceneNode.get());
	sceneNode->addChild(grid1->pSceneNode);
	sceneNode->addChild(light->pSceneNode);

	pickingCtx = api::getPixelReadContext();
	pickingCtx->setOnSelected([this](uint32 id) { onModelSelected(id); uiModelProperties->setModelSelected(currentModelSelected); });

}

bool8 Demo::isRunning() const
{
	return running;
}

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
	isActive = (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT));
	moveforward.Set(
		vDirection[0] * isActive,
		vDirection[1] * isActive,
		vDirection[2] * isActive);

	isActive = (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT));
	movebackwards.Set(
		-vDirection[0] * isActive,
		-vDirection[1] * isActive,
		-vDirection[2] * isActive);

	isActive = (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT));
	moveLeft.Cross(World::World_Y_Axis, vDirection);
	moveLeft.Set(
		moveLeft[0] * isActive,
		moveLeft[1] * isActive,
		moveLeft[2] * isActive);

	isActive = (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT));
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

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		cameraAgent->turn90();
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		cameraAgent->turnless90();
	}
}

void Demo::OnMouseScroll(double xoffset, double yoffset)
{
}

void Demo::OnWindowSizeChange(int width, int height)
{

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
	auto const pos = cameraAgent->getPosition();
	auto const dir = cameraAgent->getDirection();
	auto const rot = cameraAgent->getRotation();

	ui.textList.at(0) = format("Fps %2i ", gApp->stats.fps);
	ui.textList.at(1) = format("Camera Pos [%2.2f,%2.2f,%2.2f]", pos[0], pos[1], pos[2]);
	ui.textList.at(2) = format("Camera Dir [%2.2f,%2.2f,%2.2f]", dir[0], dir[1], dir[2]);
	ui.textList.at(3) = format("Camera Rot [%2.2f,%2.2f,%2.2f]", rot[0], rot[1], rot[2]);

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
	obj->name = filepath.substr(filepath.find_last_of("/\\") + 1);
	obj->position.Set(10 * models.size(), 2, 5 * models.size());
	mesh.create((oglElements::DrawElementTextured*)obj->pRender);

	sceneNode->addChild(obj->pSceneNode);
	obj->add2SceneWithLightShader();
	models.push_back(obj);

	sceneobjs::Model* AABB = new sceneobjs::Model(rex::Cube::getModel());
	ColorFromUID(obj->id, AABB->color);
	AABB->name = "AABB";
	AABB->add2SceneWithFlatShader();
	AABB->add2PickingLayer();
	obj->pSceneNode->addChild(AABB->pSceneNode);

	tracelog(format("Model [%s] loaded with id [%i]", obj->name.c_str(), obj->id));
		
}

void Demo::onModelSelected(uint32 id)
{
	tracelog(format("onModelSelected [%i]", id));
	currentModelSelected = 0;
	for (auto model : models) {
		if (model->id == id) {
			currentModelSelected = model;
			tracelog(format("Model [%s] [%i] has been selected", currentModelSelected->name.c_str(),currentModelSelected->id));
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

	cameraAgent->setProjection(window->width, window->height, CAMERA_FOVX, CAMERA_ZNEAR, CAMERA_ZFAR);
	cameraAgent->move(inputMovement, elapse);
	cameraAgent->rotateCamera(inputRotation, elapse);
	cameraAgent->updateViewMatrix();

	for (auto* obj : models) {
		obj->updateViewMatrix();
	}
	
	light->update(cameraAgent->getPosition());

	updateUIScene();


	inputMovement.Set(0);
	inputRotation.Set(0);
}


