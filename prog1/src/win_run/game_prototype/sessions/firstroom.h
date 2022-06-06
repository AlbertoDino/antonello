#pragma once

class GameFirstRoom : public IGameSession {
public:

	GameFirstRoom();
	~GameFirstRoom();

	virtual void loop(float32 elapse);
private:

	// Scene Objects
	std::unique_ptr<sceneobjs::Grid>				dbGrid;
	std::unique_ptr<sceneobjs::Sprite2D>			antonello;
	std::unique_ptr < sceneobjs::GenModel>			background1;

	// UI
	std::unique_ptr<sceneobjs::UiCameraProperties>	dbUiCameraProperties;

	// Model
	std::unique_ptr<oglElements::SceneNode>			sceneRoot;
	std::unique_ptr<oglElements::CameraScene>		cameraNode;
	std::unique_ptr<oglElements::Camera>			camera;
};
