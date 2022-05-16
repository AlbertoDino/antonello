#pragma once



namespace sceneobjs {

	class TextureVar {
	public:
		char8 key;
		oglElements::gl_to texture;

	};

	class PlatformMap {
	public:

		PlatformMap();
		~PlatformMap();

		oglElements::SceneNode* mapRoot;




		float32 cellHight;      //Space for empty row
		float32 tileSizeWith;   //Tile Width
		float32 tileSizeHeight; //Tile Hieght

		std::vector<TextureVar> textureHash;
	};

}

