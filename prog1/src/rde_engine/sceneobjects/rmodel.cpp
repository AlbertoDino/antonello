#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "rmodel.h"

namespace sceneobjs {

	RModel::RModel(oglElements::DrawArrayObject* drawModel) :
		position(func::CVector3f{ 0,0,0 }),
		color(func::CVector4f{ 0,0,0,1 })
	{
		id = api::getModelId(this);
		pRender = drawModel;
	}

	RModel::~RModel()
	{
	}

	void RModel::add2scene()
	{
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderFlatCtx);

		if (!rendering)
			throwError("Cannot find shaderFlat layout.");

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "color", &color);

		rendering->add2Context(this);
	}

	void RModel::updateViewMatrix()
	{
	}
}
