#pragma once

class GameL1S1 : public IGameSession {
public:

	GameL1S1();
	~GameL1S1();

	virtual void loop(float32 elapse);
private:

	// Scene Objects
	std::unique_ptr<sceneobjs::Grid> grid;

	// UI
	std::unique_ptr<sceneobjs::UiCameraProperties> uiCameraProperties;

	// Model
	std::unique_ptr<oglElements::SceneNode> sceneRoot;
	std::unique_ptr<oglElements::Camera> camera;
};
