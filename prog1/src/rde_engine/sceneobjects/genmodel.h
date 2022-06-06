#pragma once

namespace sceneobjs {


	/*
	Generic Model

	I don't like this class

	Rendering is passed from outside there is no ownership

	*/
	class GenModel : public oglElements::GameObject {
	public:

		GenModel(rex::ePreBuiltModel modelType);
		~GenModel();

		void setTextureByFilename(const std::string& filename);
		void add2scene(api::eRenderingContext ctx);

		oglElements::DrawElementTextured	*rendering;

		func::CVector4f color;
		int32			textureUnit;
	};

}