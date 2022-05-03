#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "grid.h"

namespace sceneobjs {

	Grid::Grid()
	{		
		refRender = new oglElements::DrawArrayObject();
		pSceneNode->setDebugName("Grid");

		oglElements::ArrayMesh gridCreate;
		float32 lenght = 20.0f;
		float32 height = 0.55f;
		for (float32 x = -lenght; x <= lenght; x += 0.5) {
			gridCreate.vertex3f(x, -height, lenght);
			gridCreate.vertex3f(x, -height, -lenght);
			gridCreate.vertex3f(lenght, -height, x);
			gridCreate.vertex3f(-lenght, -height, x);
		}
		gridCreate.create(&((oglElements::DrawArrayObject*)refRender)->vertexObject);
		vSet(color, colors::Green);
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