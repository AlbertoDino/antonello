 #pragma once

namespace oglElements {

	class MapTextureKey {
	public:
		char8 Key;
		int32 Index;
		gl_to Texture;
		gl_to TextureNormal;
	};

	class Map2D {
	public:

		Map2D();

		void loadFromFile(const std::string& filename);

		// Expecting txt format, for each line
		// '<Char>',"texturePath","textureNormalPath"
		void loadTextureMapKeyFromFile(const std::string& filename);

		std::vector<func::CVector3f> positions;
		std::vector<func::CVector3f> textureIndexes;

		std::vector<MapTextureKey> mapkeys;
	private:

		int32 isCharacterMappedtoTextureIndex(char c) const;

		float32 width,height;
	};
}