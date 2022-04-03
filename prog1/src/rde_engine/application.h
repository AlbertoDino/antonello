#pragma once
#include "render/local.h"
#include "win/local.h"

class Application
{
public:
	Application(HINSTANCE hInstance);

	win::GameStats		stats;
	win::StopWatch		timer;
	oglElements::WinObj gWinHandler;

	std::vector<oglElements::gl_to> textures;
	std::vector<oglElements::IRenderingCtx*> renderingLayouts;

	void init();
	void end();

	void preRender();
	void postRender();

	void calculateStats(float32 elapse);

	static void TransformSceneTree(oglElements::SceneUnitNode* node);

	oglElements::SceneUnitNode& getRoot();

private:
	std::unique_ptr<render::OglContext> renderCtx;
	oglElements::SceneUnitNode			sceneRoot;


	void loadRenderingContexts();
	void loadTextures();
};

