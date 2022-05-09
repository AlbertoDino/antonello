#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "genmodel.h"

namespace sceneobjs {

	GenModel::GenModel(oglElements::RenderingElement* rendering) :
		color(func::CVector4f{ 0,0,0,1 }),
		textureUnit(1)
	{
		refRender = rendering;
	}

	GenModel::~GenModel()
	{
	}

	void GenModel::add2scene(api::eRenderingContext ctx)
	{
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(ctx);

		if (!rendering)
			throwError("Cannot find Rendering layout.");

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, "sampler", &textureUnit);


		rendering->add2Context(this);
	}
}
