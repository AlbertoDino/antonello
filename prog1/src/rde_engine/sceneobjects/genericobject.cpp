#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "genericobject.h"

namespace sceneobjs {

	GenericObject::GenericObject() :
		position(func::CVector3f{0,0,0})		
		, roughness (0.2)
		, metallic (0.1)
		, ao (1.0)
	{
		func::vSet(color, 1.0, 0.2, 0.8,1.0);
		pRender = new oglElements::DrawElementObject();
	}

	GenericObject::~GenericObject()
	{
	}

	void GenericObject::add2scene()
	{		
		//auto rendering = set_shader_1();
		auto rendering = set_shader_2();
		
		rendering->add2Context(this);
	}

	oglElements::ShaderContext* GenericObject::set_shader_1() {
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::LightShaderCtx);

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "viewMatrix", &pSceneNode->worldview.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "color", &color);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "albedo", &color);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "metallic", &metallic);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "roughness", &roughness);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "ao", &ao);
		return rendering;
	}

	oglElements::ShaderContext* GenericObject::set_shader_2() {
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::Light_temp_2);

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "viewMatrix", &pSceneNode->view.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "objColor", &color);
		return rendering;
	}

	void GenericObject::updateViewMatrix()
	{
		func::CMatrix4f32 scale,translate,view;
		scale.Scale(CVector3f{ 1,1,1 }.data);
		translate.Translate(position.data);

		orientation.ToMatrix4(view);
		pSceneNode->view = view * translate * scale;
	}
}