#include <rdecommon.h>
#include "..\math\local.h"
#include <sstream>
#include "gltypes.h"
#include "texture.h"
#include "map2d.h"

namespace oglElements {

	bool8 CreateTexture(gl_to* textObject, const std::string imageFile, int32 unit) {
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

	Map2D::Map2D() :
		width(1)
		,height(1) {

	}

	void Map2D::loadTextureMapKeyFromFile(const std::string& filename)
	{
		FILE* fp = nullptr;
		const int bufferlen = 255;
		char line[bufferlen];

		std::vector<std::string> lines;

		fopen_s(&fp, filename.c_str(), "r");

		if (fp == nullptr)
		{
			tracelog("error in reading Platform2dMap file");
			return;
		}
		else
		{
			int32 textureUnit = 0;
			int32 index = -1;
			while (fgets(line, bufferlen, fp))
			{
				index++;
				std::vector<std::string> result;
				std::stringstream ss(line);
				std::string token;
				while (std::getline(ss, token, ','))
				{
					result.push_back(trim(token));
				}

				MapTextureKey key;
				key.Index = index;
				key.Key = result[0][0];
				
				if (!CreateTexture(&key.Texture, result[1], textureUnit++)) {
					tracelog(format("Cannot read texture %s", result[1]));
					continue;
				}

				if (!CreateTexture(&key.TextureNormal, result[2], textureUnit++)) {
					tracelog(format("Cannot read texture %s", result[2]));
					continue;
				}

				mapkeys.push_back(key);
			}
		}

		fclose(fp);
	}

	int32 Map2D::isCharacterMappedtoTextureIndex(char c) const
	{
		for (auto &map : std::as_const(mapkeys)) {
			if (map.Key == c)
				return map.Index;
		}
		return -1;
	}


	void Map2D::loadFromFile(const std::string& filename)
	{
		FILE* fp = nullptr;
		const int bufferlen = 1024*10;
		char line[bufferlen];

		std::vector<std::string> lines;

		fopen_s(&fp, filename.c_str(), "r");

		if (fp == nullptr)
		{
			tracelog("error in reading Platform2dMap file");
			return;
		}
		else
		{
			while (fgets(line, bufferlen, fp))
			{
				std::string sLine(line);
				lines.push_back(sLine);

			}
		}
		fclose(fp);

		int32 linesCount = lines.size() - 1;

		for(int32 i = 0;i< lines.size();i++)
		{
			const std::string & line = lines[linesCount-i];
			for (int32 x = 0; x < line.size(); x++) {
				char l = line[x];
				int32 textureIndex = isCharacterMappedtoTextureIndex(l);
				if (textureIndex !=-1) {
					
					positions.push_back(func::CVector3f{ x * width, i * height, 0 });
					textureIndexes.push_back(func::CVector3f({ (float32)textureIndex,(float32)textureIndex,(float32)textureIndex }));
				}
			}
		}
	}
}