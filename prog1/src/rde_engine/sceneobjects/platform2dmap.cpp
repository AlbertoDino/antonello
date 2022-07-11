#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "platform2dmap.h"

namespace sceneobjs {

	Platform2DMap::Platform2DMap()
		: cellHight(10)
		, tileSizeWith(1.5)
		, tileSizeHeight(2.5)
		, map2d(0)
	{

		for (int32 i = 0; i < 10; i++)
		{
			units[i] = i;
		}

		refRender = rendering = new NormalModelRenderingInstanced();
	}

	Platform2DMap::~Platform2DMap()
	{
	}


	void Platform2DMap::setMap2D(oglElements::Map2D* map)
	{
		map2d = map;
	}

	void  Platform2DMap::createRendering()
	{
		

		std::vector<CVector3f> positions = {
			CVector3f({0,0,0}),
			CVector3f({1,0,0}),
			CVector3f({2,0,0}),
			CVector3f({3,0,0}),
			CVector3f({4,0,0})
		};

		std::vector<func::CVector3f> textureIndexes = {
			func::CVector3f({0,0,0}),
			func::CVector3f({1,1,1}),
			func::CVector3f({1,1,1}),
			func::CVector3f({2,2,2}),
			func::CVector3f({3,3,3}),
		};

		

		//map2d->positions = positions;
		//map2d->textureIndexes= textureIndexes;


		if (rendering->vertexObject.VAO)
			return;

		for (const auto& text : std::as_const(map2d->mapkeys))
		{
			rendering->textures.push_back(text.Texture);
			rendering->textures.push_back(text.TextureNormal);
		}

		rendering->instanceCount = map2d->positions.size();
		rendering->vertexObject = rex::Rectangle::getModel();

		//Instance attribute

		glBindVertexArray(rendering->vertexObject.VAO);

		GLuint offset = 0;
		glGenBuffers(1, &rendering->vertexObject.INS);
		glBindBuffer(GL_ARRAY_BUFFER, rendering->vertexObject.INS);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(CVector3f) * map2d->positions.size()) + (sizeof(func::CVector3f) * map2d->textureIndexes.size()), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(CVector3f) * map2d->positions.size(), map2d->positions.data());
		offset += sizeof(CVector3f) * map2d->positions.size();
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(func::CVector3f) * map2d->textureIndexes.size(), map2d->textureIndexes.data());

		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(CVector3f) * map2d->positions.size()));


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
		int32 i = 0;
		for (auto& text : map2d->mapkeys)
		{
			std::string unifNameColorMap = format("colorMap%i", textureIndex);
			std::string unifNameNormalMap = format("normalMap%i", textureIndex);
			textureIndex++;

			shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, unifNameColorMap.c_str(), &units[i++]);
			shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, unifNameNormalMap.c_str(), &units[i++]);
		}

		ctx->add2Context(this);
	}


	void NormalModelRenderingInstanced::render() const
	{

		for (const auto& text : std::as_const(textures))
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

		for (const auto& text : std::as_const(textures))
		{
			text.unbind();
		}

	}

}