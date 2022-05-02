#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "grid.h"

namespace sceneobjs {

	Grid::Grid()
	{
		func::vSet(color, 1.0f, 0.0f, 1.0f, 1.0f);
		refRender = new oglElements::DrawArrayObject();
		pSceneNode->setDebugName("Grid");
	}

	Grid::~Grid()
	{	
	}

	void Grid::add2scene()
	{
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderFlat);
		
		if (!rendering)
			throwError("Cannot find shaderFlat layout.");
		
		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "color", &color);

		rendering->add2Context(this);
	}

	void Grid::removeFromScene()
	{

	}

}