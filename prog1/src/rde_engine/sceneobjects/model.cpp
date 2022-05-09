#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "model.h"

namespace sceneobjs {
	/*
	This has to be refactor:

	1- in one constructor the refRender is created within the class
	2- in a second construct is passed from outside
	3- what is model vs genmodel vs normalmodel ?
	*/
	Model::Model() 
	{
		refRender = new oglElements::DrawElementTextured(api::getDefaultTexture());
		init();
	}

	Model::Model(oglElements::RenderingElement* rndElem)
	{
		refRender = rndElem;
		init();
	}

	Model::~Model()
	{
	}

	void Model::init() {
		func::vSet(color, 1.0, 1.0, 1.0, 1.0);
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
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderFlat);

		if (!rendering)
			throwError("Cannot find shaderFlat layout.");

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V4f, "color", &color);

		rendering->add2Context(this);
	}

	void Model::add2SceneWithLightShader()
	{
		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderLight);

		if (!rendering)
			throwError("Cannot find ShaderLight layout.");

		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "viewMatrix", &pSceneNode->view.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, "sampler", &textureUnit);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V3f, "objColor", &color);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "objSpecularIntensity", &specularIntensity);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1f, "objSpecularPower", &specularPower);

		rendering->add2Context(this);
	}

}