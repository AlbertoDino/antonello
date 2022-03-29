#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include <format>
#include "demo.h"

using namespace func;

Demo::Demo() : running{ true }
{

	cameraAgent = std::make_unique<oglElements::Camera>();
	sceneNode	= std::make_unique<oglElements::SceneUnitNode>();
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
	ui.textList.push_back("press v : reset camera");
	uiCtx->render(&ui);

	uiFileBrowser = std::make_unique<sceneobjs::UiFileBrowser>();
	uiFileBrowser->set_mesh_load_callback(
		[this](std::string filepath) { addObjectFromFile(filepath); });
	ui.uiComponents.push_back(uiFileBrowser.get());

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
	grid1->color[0] = 0.3F;
	grid1->color[1] = 0.17F;
	grid1->color[2] = 0.6F;
	grid1->add2scene();

	light->position.Set(-150, 80, 3);
	light->add2scene();
	
	gApp->getRoot().addChild(cameraNode);
	
	sceneNode->setDebugName("sceneNode");
	cameraNode->addChild(sceneNode.get());
	sceneNode->addChild(grid1->pSceneNode);
	sceneNode->addChild(light->pSceneNode);


	
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
	isActive = (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT));
	moveforward.Set(
		vDirection[0] * isActive,
		vDirection[1] * isActive,
		vDirection[2] * isActive);

	isActive = (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT));
	movebackwards.Set(
		-vDirection[0] * isActive,
		-vDirection[1] * isActive,
		-vDirection[2] * isActive);

	isActive = (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT));
	moveLeft.Cross(World::World_Y_Axis, vDirection);
	moveLeft.Set(
		moveLeft[0] * isActive,
		moveLeft[1] * isActive,
		moveLeft[2] * isActive);

	isActive = (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT));
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
		cameraAgent->reset();
	}
}

void Demo::OnMouseScroll(double xoffset, double yoffset)
{
}

void Demo::OnWindowSizeChange(int width, int height)
{
	window->width = width;
	window->height = height;
}

void Demo::OnWindowClose()
{
	running = false;
}

void Demo::OnPositionCursorChange(double xposd, double yposd)
{
	float32 xpos = static_cast<float32>(xposd);
	float32 ypos = static_cast<float32>(yposd);


	float32 xOffset = xpos - lastRotation[0];
	float32 yOffset = lastRotation[1] - ypos;	

	lastRotation[0] = xpos;
	lastRotation[1] = ypos;

	inputRotation.Set(xOffset, -yOffset, 0);
}


void Demo::updateUIScene()
{
	auto const pos = cameraAgent->getPosition();
	auto const dir = cameraAgent->getDirection();

	ui.textList.at(0) = format("Fps %2i ", gApp->stats.fps);
	ui.textList.at(1) = format("Camera Pos [%2.2f,%2.2f,%2.2f]", pos[0], pos[1], pos[2]);
	ui.textList.at(2) = format("Camera Dir [%2.2f,%2.2f,%2.2f]", dir[0], dir[1], dir[2]);

}

void Demo::addObjectFromFile(std::string filepath)
{
	oglElements::Mesh mesh;
	if (!mesh.loadFromFile(filepath)) {
		throwError("Cannot load mesh from file");
		return;
	}


	sceneobjs::GenericObject* obj = new sceneobjs::GenericObject();

	obj->position.Set(30 * objects.size(), 2, 20 * objects.size());
	mesh.create((oglElements::DrawElementObject*)obj->pRender);

	sceneNode->addChild(obj->pSceneNode);
	obj->add2scene();
	objects.push_back(obj);
}

void Demo::loop(float32 elapse)
{
	cameraAgent->setProjection(window->width, window->height, CAMERA_FOVX, CAMERA_ZNEAR, CAMERA_ZFAR);
	cameraAgent->move(inputMovement, elapse);
	cameraAgent->rotateCamera(inputRotation, elapse);
	cameraAgent->updateViewMatrix();

	for (auto* obj : objects) {
		obj->updateViewMatrix();
	}
	light->updateViewMatrix();

	updateUIScene();


	inputMovement.Set(0);
	inputRotation.Set(0);
}


