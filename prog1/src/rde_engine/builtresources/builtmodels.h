#pragma once

namespace rex {

	class Cube {
	public:
		static oglElements::DrawArrayObject* getModel();

		private:
			static oglElements::DrawArrayObject* cube;
	};


	class Rectangle {
	public:
		static oglElements::DrawArrayObjectWithTexture* getModel();
		static void createRectangle(oglElements::DrawArrayObjectWithTexture* draw);
	private:
		static oglElements::DrawArrayObjectWithTexture* rectangle;

		
	};

}