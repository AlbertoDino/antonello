#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "light.h"

namespace sceneobjs {

	Light::Light()
	{
		color.Set(500.0f, 500.0f, 500.0f);
		position.Set( 1.5f, 3.5f, 3.0f );
		Strength = 100.0f;
	}

	Light::~Light()
	{
	}

	void Light::add2scene()
	{
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::LightShaderCtx);
		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "lightPosition", &position);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "lightColor", &color);

		rendering->add2Context(this);
	}

	void Light::updateViewMatrix()
	{
		pSceneNode->view.Translate(position.data);
	}

}