#include <rde_common/lib.h>
#include "render/local.h"
#include "builtresources/local.h"
#include "header/api.h"
#include "win/local.h"
#include "application.h"


Application::Application(HINSTANCE hInstance)
{
	gWinHandler.osWindowHandler = hInstance;

	renderCtx = std::make_unique< render::OglContext>();
}

void Application::init()
{
	sceneRoot.pParent = &sceneRoot;
	sceneRoot.setDebugName("root");
	renderCtx->init(&gWinHandler);
	
	loadRenderingContexts();

	for (auto const& renderingCtx : renderingLayouts) {
		renderingCtx->init(&gWinHandler);
	}
}

void Application::end()
{
	for (auto const& renderingCtx : renderingLayouts) {
		renderingCtx->end();
	}
	renderCtx->end();
}

void Application::preRender() {
	renderCtx->pre_render();
}

void Application::postRender() {

	TransformSceneTree(&getRoot());

	for (auto const& renderingLayout : std::as_const(renderingLayouts)) {
		renderingLayout->render();
	}

	renderCtx->post_render();
}

void Application::calculateStats(float32 elapse)
{
	static int32	frames_count = 0;

	frames_count++;
	stats.accumElapse += elapse;
	
	if (stats.accumElapse >= 1)
	{
		stats.fps = frames_count;
		stats.accumElapse = 0;
	}

}

void Application::TransformSceneTree(oglElements::SceneUnitNode* node)
{
	node->worldprojection = node->pParent->worldprojection * (node->projection);
	node->worldview = node->pParent->worldview * (node->view);
	//node->worldview.ExtractRotationMatrix(*node->pNormal);   // Normal matrix ?
	node->worldmvp = (node->worldprojection) * (node->worldview);

	int32 childCount = node->count();
	node = node->pFirstChild;
	for (int32 i = 0; i < childCount; i++) {
		TransformSceneTree(node);
		node = node->pNextNode;
	}
}

oglElements::SceneUnitNode& Application::getRoot()
{
	return sceneRoot;
}



/*
===============================================================================
LOAD
===============================================================================
*/

void Application::loadRenderingContexts()
{
	colors::InitColors();

	rex::FlatShader flShader;
	if (flShader.init())
	{
		// Add Rendering Layout
		oglElements::ShaderContext* layout = new oglElements::ShaderContext(api::eRenderingContext::ShaderFlatCtx);
		layout->shader.init(flShader.programId);
		renderingLayouts.push_back(layout);
		tracelog(format("shader: FlatShader [%i] added.", flShader.programId));
	}
	else {
		tracelog("Error loading flat shader");
	}	
	//---------------------------------------------------
	rex::LightShader lgShader;
	if (lgShader.init())
	{
		oglElements::ShaderContext* layout = new oglElements::ShaderContext(api::eRenderingContext::LightShaderCtx);
		layout->shader.init(lgShader.programId);
		renderingLayouts.push_back(layout);
		tracelog(format("shader: LightShader [%i] added.", lgShader.programId));
	}
	else {
		tracelog("Error loading LightShader");
	}	
	//---------------------------------------------------
	rex::Light_temp_2 lgTemp2;
	if (lgTemp2.init())
	{
		// Add Rendering Layout
		oglElements::ShaderContext* layout = new oglElements::ShaderContext(api::eRenderingContext::Light_temp_2);
		layout->shader.init(lgTemp2.programId);
		renderingLayouts.push_back(layout);
		tracelog(format("shader: Light_temp_2 [%i] added.", lgTemp2.programId));
	}
	else {
		tracelog("Error loading Light_temp_2");
	}
	//---------------------------------------------------
	renderingLayouts.push_back(new render::UIContext(api::eRenderingContext::UICxt));

}


