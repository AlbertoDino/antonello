#pragma once
#include <3rdparty/lib.h>
#include <rde_common/lib.h>
#include <rde_engine/lib.h>


class Demo : public render::WinEventHandler {
public:
	Demo();
	~Demo();

	void init(oglElements::WinObj* gWininstance);

	bool8 isRunning() const;

	virtual void OnKey(int key, int scancode, int action, int mods);
	virtual void OnMouseScroll(double xoffset, double yoffset);
	virtual void OnWindowSizeChange(int width, int height);
	virtual void OnWindowClose();
	virtual void OnPositionCursorChange(double xpos, double ypos);


	void addObjectFromFile(std::string filepath);

	void loop(float32 elapse);

private:

	void updateUIScene();

	oglElements::WinObj* window;

	CVector3f inputMovement, inputRotation, lastRotation;

	std::unique_ptr<oglElements::SceneUnitNode> sceneNode;
	std::unique_ptr<sceneobjs::Grid> grid1;
	std::unique_ptr<sceneobjs::Light> light;
	std::unique_ptr<oglElements::Camera> cameraAgent;
	std::unique_ptr<sceneobjs::UiFileBrowser> uiFileBrowser;
	std::vector<sceneobjs::GenericObject*> objects;
	bool8 running;
	
	render::UIScene ui;
};