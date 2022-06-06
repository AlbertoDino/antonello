#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "genmodel.h"

namespace sceneobjs {

	GenModel::GenModel(rex::ePreBuiltModel modelType) :
		color(func::CVector4f{ 0,0,0,1 }),
		textureUnit(0)
	{
		refRender = rendering = new oglElements::DrawElementTextured();
		rendering->textureObject = api::getDefaultTexture();
		switch (modelType)
		{
		case rex::cube:
			
			break;
		case rex::sphere:
			rendering->vertexObject = rex::Sphere::getModel(1.0f, 36, 18);
			break;
		case rex::rectangle:
			rendering->vertexObject = rex::Rectangle::getModel();
			break;
		default:
			break;
		}
	}

	GenModel::~GenModel()
	{
		if (rendering != 0)
			delete rendering;
	}

	void GenModel::setTextureByFilename(const std::string& filename)
	{
		oglElements::Texture texture;
		texture.loadImageByFilename(filename);
		texture.create(&rendering->textureObject, GL_TEXTURE_2D, textureUnit);
		texture.bind();
		texture.setFiltering(GL_LINEAR, GL_LINEAR);
		texture.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		texture.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		texture.generateMipmap();
		texture.save();
		texture.unbind();
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
