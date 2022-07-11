#pragma once


class GmS1E3 : public IGameSession {
public:

	GmS1E3();
	~GmS1E3();

	virtual void OnKey(int key, int scancode, int action, int mods);
	virtual void OnMouseScroll(double xoffset, double yoffset);
	virtual void OnWindowSizeChange(int width, int height);
	virtual void OnWindowClose();
	virtual void OnPositionCursorChange(double xpos, double ypos);
	virtual void loop(float32 elapse);

	virtual void Show();
	virtual void Hide();

	void handleInput(float32 elapse);

private:
	GLFWwindow* glWindowHandler;

	std::unique_ptr<oglElements::TaskQueue> taskQueue;
	std::unique_ptr<FixedFrameInteraction>  interaction;
	oglElements::TaskExecuter taskExecuter;

	// Scene Objects
	std::unique_ptr<sceneobjs::Grid>				dbGrid;
	std::unique_ptr<sceneobjs::Sprite2D>			antonello;

	// Model
	std::unique_ptr<oglElements::SceneNode>			sceneRoot;
	std::unique_ptr<oglElements::CameraScene>		cameraNode;
	std::unique_ptr<oglElements::ThirdCameraView>	camera;
};