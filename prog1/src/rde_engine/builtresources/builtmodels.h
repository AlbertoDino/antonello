#pragma once

namespace rex {

	enum ePreBuiltModel : int32 {
		cube,
		sphere,
		rectangle
	};

	class Cube {
	public:
		static const oglElements::gl_vertexObject& getModel();

		private:
			static oglElements::gl_vertexObject cube;
	};

	// This Rectangle does not use Vertex but 2 data buffer for Pos and UV
	class RectangleForSprite {
	public:
		const static oglElements::gl_vertexObject& getModel();
	private:
		static oglElements::gl_vertexObject rectangle;
		
	};

	class Rectangle {
	public:
		const static oglElements::gl_vertexObject& getModel();
	private:
		static oglElements::gl_vertexObject rectangle;

	};


	class Sphere {
	public:
		static const oglElements::gl_vertexObject& getModel(float32 fRadius, int32 iSlices, int32 iStacks);
	private:
		static oglElements::gl_vertexObject sphere;
	};

}