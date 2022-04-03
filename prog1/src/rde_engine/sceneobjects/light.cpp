#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "light.h"

namespace sceneobjs {

	Light::Light()
	{
		color.Set(1.0f, 1.0f, 1.0f);
		direction.Set( 1.f, 0.0f, 0.0f );
		ambientIntensity = 0.4f;
		diffuseIntensity = 0.3f;

	}

	Light::~Light()
	{
	}

	void Light::update(const CVector3f& _cameraPos)
	{
		cameraPos = _cameraPos;
	}

	void Light::add2scene()
	{
		auto rendering = set_shader_temp2();


		rendering->add2Context(this);
	}

	oglElements::ShaderContext* Light::set_shader_temp2()
	{
		direction.Normalize();
			
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::Light_temp_2);
		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "gDirectionalLight.Color", &color.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "gDirectionalLight.Direction", &direction.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "gDirectionalLight.AmbientIntensity", &ambientIntensity);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "gDirectionalLight.DiffuseIntensity", &diffuseIntensity);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "camPos", &cameraPos.data);
		return rendering;
	}


}