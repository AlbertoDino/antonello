#pragma once

namespace sceneobjs {


	/*
	Generic Model

	I don't like this class

	Rendering is passed from outside there is no ownership

	*/
	class GenModel : public oglElements::GameObject {
	public:

		GenModel(oglElements::RenderingElement* drawModel);
		~GenModel();

		void add2scene(api::eRenderingContext ctx);

		func::CVector4f color;
		int32			textureUnit;
	};

}