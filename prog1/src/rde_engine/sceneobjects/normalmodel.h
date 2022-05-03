#pragma once

namespace sceneobjs {


	class NormalModelRendering : public oglElements::RenderingElement {
	public:
		oglElements::gl_vertexObject	vertexObject;
		oglElements::gl_to				textureObject;
		oglElements::gl_to				textureNormal;

		virtual void render() const;
	};

	class NormalModel : public oglElements::SceneObject {
	public:

		NormalModel();				

		void setModel(rex::ePreBuiltModel model);
		void setTextureByFilename(const std::string& filename);
		void setNormalTextureByFilename(const std::string& filename);

		void add2scene();
		void updateViewMatrix();
		NormalModelRendering* getRendering();

		func::CVector3f position;
		func::CVector3f scale;
		func::CVector4f color;
		std::string		name;
		uint32			id;		
		func::Quaternion orientation;
	private:
		int32 textureUnit;
		int32 textureNormalUnit;
		NormalModelRendering		*rendering;
	};

}