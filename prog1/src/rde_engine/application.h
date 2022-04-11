#pragma once
#include "render/local.h"
#include "win/local.h"

class Application
{
public:
	Application(HINSTANCE hInstance);

	win::GameStats								stats;
	win::StopWatch								timer;
	oglElements::WinObj							gWinHandler;
	std::vector<oglElements::gl_to>				textures;
	std::vector<oglElements::IRenderingCtx*>	renderingLayouts;

	void init();
	void end();
	void resize(int32 width, int32 height);
	void render();

	void calculateStats(float32 elapse);

	static void TransformSceneTree(oglElements::SceneUnitNode* node);

	oglElements::SceneUnitNode& getRoot();
	render::PixelReadContext*	getPixelReadCtx();

private:
	std::unique_ptr<render::OglContext>			renderCtx;
	std::unique_ptr<render::PixelReadContext>	pixelReadCtx;
	oglElements::SceneUnitNode					sceneRoot;

	void loadRenderingContexts();
	void loadTextures();
};

