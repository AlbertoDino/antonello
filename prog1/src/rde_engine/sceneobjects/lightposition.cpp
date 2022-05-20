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
		auto rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderNormalTextureLight);		
		shaderNormal.shaderValues = rendering->shader;
		shaderNormal.shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "lightPos", &lightPosition.data);
		shaderNormal.shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "viewPos", &cameraPosition.data);
		shaderNormal.shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "ambientColor", &ambientColor.data);
		rendering->add2Context(&shaderNormal);

		//---
		rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderNormalTextureLightInstanced);
		shaderNormalInstance.shaderValues = rendering->shader;
		shaderNormalInstance.shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "lightPos", &lightPosition.data);
		shaderNormalInstance.shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "viewPos", &cameraPosition.data);
		shaderNormalInstance.shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "ambientColor", &ambientColor.data);
		rendering->add2Context(&shaderNormalInstance);
	}

	void LightPosition::update(const CVector3f& cameraPos)
	{
		cameraPosition = cameraPos;
	}

}