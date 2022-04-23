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
	private:
		static oglElements::DrawArrayObjectWithTexture* rectangle;

		
	};

}