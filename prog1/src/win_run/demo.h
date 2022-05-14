#pragma once
#include <3rdparty/lib.h>
#include <rde_common/lib.h>
#include <rde_engine/lib.h>


class Demo : public render::WinEventHandler {
public:
	Demo();
	~Demo();

	void init();

	bool8 isRunning() const;

	virtual void OnKey(int key, int scancode, int action, int mods);
	virtual void OnMouseScroll(double xoffset, double yoffset);
	virtual void OnWindowSizeChange(int width, int height);
	virtual void OnWindowClose();
	virtual void OnPositionCursorChange(double xpos, double ypos);


	void addObjectFromFile(std::string filepath);

	void onModelSelected(uint32 id);

	void loop(float32 elapse);

private:
	void handleInput();
	void updateUIScene();

	oglElements::WinObj* window;

	CVector3f inputMovement, inputRotation, lastRotation;

	std::unique_ptr<oglElements::SceneNode> sceneNode;
	std::unique_ptr<sceneobjs::Grid> grid1;
	std::unique_ptr<sceneobjs::Light> light;
	std::unique_ptr<oglElements::Camera> cameraAgent;
	std::unique_ptr<sceneobjs::UiModelProperties> uiModelProperties;
	std::unique_ptr<sceneobjs::UILightProperties> uiLightProperties;
	std::unique_ptr<sceneobjs::UILightPositionProperties> uiLightPosProperties;
	std::unique_ptr<sceneobjs::UiCameraProperties> uiCameraProperties;
	std::vector<sceneobjs::Model*> models;

	bool8 running;
	std::unique_ptr<sceneobjs::Sprite2D> sprite;
	std::unique_ptr<sceneobjs::GenModel> sphere;


	std::unique_ptr<sceneobjs::LightPosition> lightPosition;
	std::unique_ptr<sceneobjs::NormalModel> sphereNormal;

	sceneobjs::Model* currentModelSelected;
	
	render::UITextList uiText;
	render::PixelReadContext* pickingCtx;


	std::unique_ptr<oglElements::TaskQueue> taskQueue;
	win::TaskExecuter taskExecuter;
	std::unique_ptr<win::LinearSurface> surface;

};