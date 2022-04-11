#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "model.h"

namespace sceneobjs {

	Model::Model() 
	{
		pRender = new oglElements::DrawElementTextured(api::getDefaultTexture());
		init();
	}

	Model::Model(oglElements::RenderingElement* rndElem)
	{
		pRender = rndElem;
		init();
	}

	Model::~Model()
	{
	}

	void Model::init() {
		id = api::getModelId(this);
		func::vSet(color, 1.0, 1.0, 1.0, 1.0);
		position = func::CVector3f{ 0,0,0 };
		specularPower = 16.0f;
		specularIntensity = 1.0f;
		textureUnit = 0;
	}

	void Model::add2PickingLayer()
	{
		render::PixelReadContext* pickingUpLayer = api::getPixelReadContext();

		if (!pickingUpLayer)
			throwError("Cannot find pickingUpLayer layout.");

		shaderValues = pickingUpLayer->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "color", &color);

		pickingUpLayer->add2Context(this);
	}

	void Model::add2SceneWithFlatShader()
	{
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderFlatCtx);

		if (!rendering)
			throwError("Cannot find shaderFlat layout.");

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "color", &color);

		rendering->add2Context(this);
	}

	void Model::add2SceneWithLightShader()
	{
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::Light_temp_2);

		if (!rendering)
			throwError("Cannot find Light_temp_2 layout.");

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "viewMatrix", &pSceneNode->view.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, "sampler", &textureUnit);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "objColor", &color);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "objSpecularIntensity", &specularIntensity);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "objSpecularPower", &specularPower);

		rendering->add2Context(this);
	}

	void Model::updateViewMatrix()
	{
		func::CMatrix4f32 scale, translate, view;
		scale.Scale(CVector3f{ 1,1,1 }.data);
		translate.Translate(position.data);

		orientation.ToMatrix4(view);
		pSceneNode->view = view * translate * scale;
	}
}