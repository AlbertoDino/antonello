#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "platform2dmap.h"

namespace sceneobjs {

	Platform2DMap::Platform2DMap()
		: cellHight(10)
		, tileSizeWith(1.5)
		, tileSizeHeight(2.5)
	{
		refRender = rendering = new NormalModelRenderingInstanced();
	}

	Platform2DMap::~Platform2DMap()
	{
	}

	bool8 CreateTexture(oglElements::gl_to* textObject, const std::string imageFile, int32 unit) {
		oglElements::Texture texture;
		auto resp = texture.loadImageByFilename(imageFile);

		if (!resp.loadSuccessfully) {
			tracelog(format("Cannot load texture %s \n", imageFile));
			return false;
		}

		texture.create(textObject, GL_TEXTURE_2D, unit);
		texture.bind();
		texture.setFiltering(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
		texture.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		texture.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		texture.generateMipmap();
		texture.save();
		texture.unbind();

		return true;
	}

	void Platform2DMap::createTexturePool(const std::vector<ImageMap>& map)
	{
		int32 index = 0;
		int32 textureUnit = 0;
		for (auto imageR : map) {

			TextureMap texRecord;
			texRecord.key = imageR.key;

			if (!CreateTexture(&texRecord.texture, imageR.imagePath, textureUnit++))
				continue;

			if (!CreateTexture(&texRecord.textureNormal, imageR.imageNormalPath, textureUnit++))
				continue;

			texRecord.index = index++;
			textureHash.push_back(texRecord);
		}

	}

	void Platform2DMap::generateByFile(const std::string& mapfile)
	{

		positions = {
			{0,0,0},
			{1,0,0},
			{2,0,0},
			{3,0,0},
			{4,0,0},
		};

		textureIndexes = {
			{0},
			{0},
			{0},
			{0},
			{0},
		};
	}


	void  Platform2DMap::createRendering()
	{
		if (rendering->vertexObject.VAO)
			return;

		for (const auto &text : std::as_const(textureHash))
		{
			rendering->textures.push_back(text.texture);
			rendering->textures.push_back(text.textureNormal);
		}

		rendering->instanceCount = 5;
		rendering->vertexObject = rex::Rectangle::getModel();

		//Instance attribute

		glBindVertexArray(rendering->vertexObject.VAO);

		GLuint offset = 0;
		glGenBuffers(1, &rendering->vertexObject.INS);
		glBindBuffer(GL_ARRAY_BUFFER, rendering->vertexObject.INS);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(Vector3f) * positions.size()) + (sizeof(int32) * textureIndexes.size()), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Vector3f) * positions.size(), positions.data());
		offset += sizeof(Vector3f) * positions.size();
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(GL_INT) * textureIndexes.size(), textureIndexes.data());

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 1, GL_INT, GL_FALSE, 0, (void*)(sizeof(Vector3f) * positions.size()));
		
		
		glVertexAttribDivisor(4, 1); // will provid the value per 1 instance not per vertex
		glVertexAttribDivisor(5, 1); // will provid the value per 1 instance not per vertex
		
		glBindVertexArray(0);
	}

	void Platform2DMap::add2scene()
	{
		createRendering();

		oglElements::ShaderContext* ctx = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderNormalTextureLightInstanced);

		shaderValues = ctx->shader;

		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "model", &pSceneNode->worldview.data);
		
		
		int32 textureIndex = 1;
		for (auto &text : textureHash)
		{
			std::string unifNameColorMap = format("colorMap%i", textureIndex);
			std::string unifNameNormalMap = format("normalMap%i", textureIndex);
			textureIndex++;

			shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, unifNameColorMap.c_str(), &text.texture.unit);
			shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, unifNameNormalMap.c_str(), &text.textureNormal.unit);
		}
		
		ctx->add2Context(this);
	}


	void NormalModelRenderingInstanced::render() const
	{
		
		for (const auto &text : std::as_const(textures))
		{
			text.activeBind();
		}

		glBindVertexArray(vertexObject.VAO);

		glDrawElementsInstanced(
			vertexObject.drawMode,
			vertexObject.count,
			GL_UNSIGNED_INT,
			0,
			instanceCount);

		glBindVertexArray(0);

		for (const auto &text : std::as_const(textures))
		{
			text.unbind();
		}
		
	}

}