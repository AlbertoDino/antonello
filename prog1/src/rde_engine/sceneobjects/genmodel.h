#pragma once

namespace sceneobjs {


	/*
	Generic Model

	I don't like this class

	Rendering is passed from outside there is no ownership

	*/
	class GenModel : public oglElements::SceneObject {
	public:

		GenModel(oglElements::RenderingElement* drawModel);
		~GenModel();

		void add2scene(api::eRenderingContext ctx);
		void updateViewMatrix();

		func::CVector3f position;
		func::CVector4f color;
		std::string		name;
		uint32			id;
		int32			textureUnit;
		func::Quaternion orientation;
	};

}