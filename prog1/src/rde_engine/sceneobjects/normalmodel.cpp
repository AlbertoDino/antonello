#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "normalmodel.h"

namespace sceneobjs {

	void NormalModelRendering::render() const
	{
		textureObject.activeBind();
		textureNormal.activeBind();

		glBindVertexArray(vertexObject.VAO);
		glDrawElements(vertexObject.drawMode, vertexObject.count, GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		textureNormal.unbind();
		textureObject.unbind();
	}

	NormalModel::NormalModel() : textureUnit(0), textureNormalUnit(1)
	{
		refRender = rendering = new NormalModelRendering();
	}

	void NormalModel::setModel(rex::ePreBuiltModel model)
	{
		switch (model) {
		case rex::ePreBuiltModel::sphere:
			rendering->vertexObject = rex::Sphere::getModel(1.0f, 36, 18);
			break;
		case rex::ePreBuiltModel::rectangle:
			rendering->vertexObject = rex::Rectangle::getModel();
			break;
		default:
			throwError("Model not supported");
			break;
		};
	}

	void NormalModel::setTextureByFilename(const std::string& filename)
	{
		oglElements::Texture texture;
		texture.loadImageByFilename(filename);
		texture.create(&rendering->textureObject, GL_TEXTURE_2D, textureUnit);
		texture.bind();
		texture.setFiltering(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		texture.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		texture.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		texture.generateMipmap();
		texture.save();
		texture.unbind();
	}

	void NormalModel::setNormalTextureByFilename(const std::string& filename)
	{
		oglElements::Texture texture;
		texture.loadImageByFilename(filename);
		texture.create(&rendering->textureNormal, GL_TEXTURE_2D, textureNormalUnit);
		texture.bind();
		texture.setFiltering(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		texture.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		texture.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		texture.generateMipmap();
		texture.save();
		texture.unbind();
	}

	void NormalModel::add2scene()
	{
		oglElements::ShaderContext* ctx = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderNormalTextureLight);

		shaderValues = ctx->shader;

		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "model", &pSceneNode->worldview.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, "colorMap", &textureUnit);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, "normalMap", &textureNormalUnit);

		ctx->add2Context(this);
	}

	NormalModelRendering* NormalModel::getRendering()
	{
		return rendering;
	}
	
}