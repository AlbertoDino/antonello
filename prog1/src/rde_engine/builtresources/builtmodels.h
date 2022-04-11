#pragma once

namespace rex {

	class Cube {
	public:
		static oglElements::DrawArrayObject* getModel();

		private:
			static oglElements::DrawArrayObject* cube;
	};

}