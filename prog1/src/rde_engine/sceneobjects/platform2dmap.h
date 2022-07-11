#pragma once



namespace sceneobjs {

	class ImageMap {
	public:
		char8 key;
		std::string imagePath;
		std::string imageNormalPath;
	};

	class TextureMap {
	public:
		char8 key;
		int32 index;
		oglElements::gl_to texture;
		oglElements::gl_to textureNormal;
	};

	class NormalModelRenderingInstanced : public oglElements::RenderingElement {
	public:
		std::vector<oglElements::gl_to> textures;
		oglElements::gl_vertexObject	vertexObject;
		int32 instanceCount;
		virtual void render() const;

	};

	class Platform2DMap : public oglElements::GameObject {
	public:

		Platform2DMap();
		~Platform2DMap();

		void setMap2D(oglElements::Map2D* map);
		void add2scene();

		float32 cellHight;      //Space for empty row
		float32 tileSizeWith;   //Tile Width
		float32 tileSizeHeight; //Tile Hieght


	private:

		// Create Opengl objects supporting instancing
		void createRendering();

		oglElements::Map2D* map2d;

		//std::vector<TextureMap> textureHash;
		NormalModelRenderingInstanced* rendering;

		//std::vector<glm::vec3> positions;
		//std::vector<int32> textureIndexes;
		int32 units[10];
	};

}

