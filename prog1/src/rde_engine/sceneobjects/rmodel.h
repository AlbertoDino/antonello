#pragma once

namespace sceneobjs {

	class RModel : public oglElements::SceneShaderObject {
	public:

		RModel(oglElements::DrawArrayObject* drawModel);
		~RModel();

		void add2scene();
		void updateViewMatrix();

		func::CVector3f position;
		func::CVector4f color;
		std::string		name;
		uint32			id;
	};

}