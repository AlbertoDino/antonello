#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "lightposition.h"

namespace sceneobjs {



	LightPosition::LightPosition()
	{
		lightPower = 40.0;
		lightPosition.Set(9, -5, -4);
		ambientColor.Set(0.2f, 0.2f, 0.2f, 1.0f);
		diffuseColor.Set(0.8f, 0.8f, 0.8f, 0.8f);
	}

	void LightPosition::add2scene()
	{
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderNormalTextureLight);
		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "lightPos", &lightPosition.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "viewPos", &cameraPosition.data);		
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "ambientColor", &ambientColor.data);
		/*shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "diffuseColor", &diffuseColor.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "lightPower", &lightPower);
		*/
		rendering->add2Context(this);
	}

	void LightPosition::update(const CVector3f& cameraPos)
	{
		cameraPosition = cameraPos;
	}

}