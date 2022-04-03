#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "model.h"

namespace sceneobjs {

	uint32 Model::modelIdCount = 1;

	Model::Model() :
		position(func::CVector3f{0,0,0})		
		, specularPower (16.0f)
		, specularIntensity (1.0f)
	{
		id = Model::getNextId();
		func::vSet(color, 1.0, 0.2, 0.8,1.0);
		pRender = new oglElements::DrawElementObject();
	}

	Model::~Model()
	{
	}

	void Model::add2scene()
	{		
		//auto rendering = set_shader_1();
		auto rendering = set_shader_2();
		
		rendering->add2Context(this);
	}

	oglElements::ShaderContext* Model::set_shader_1() {
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::LightShaderCtx);

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "viewMatrix", &pSceneNode->worldview.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "color", &color);

		return rendering;
	}

	oglElements::ShaderContext* Model::set_shader_2() {
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::Light_temp_2);

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "viewMatrix", &pSceneNode->view.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "objColor", &color);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "objSpecularIntensity", &specularIntensity);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "objSpecularPower", &specularPower);
		return rendering;
	}

	uint32 Model::getNextId()
	{
		return Model::modelIdCount++;
	}

	void Model::updateViewMatrix()
	{
		func::CMatrix4f32 scale,translate,view;
		scale.Scale(CVector3f{ 1,1,1 }.data);
		translate.Translate(position.data);

		orientation.ToMatrix4(view);
		pSceneNode->view = view * translate * scale;
	}
}