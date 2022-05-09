#pragma once


namespace sceneobjs {

	class Grid : public oglElements::GameObject {
	public:
		Grid();
		~Grid();

		Color color;

		void add2scene();
		void removeFromScene();
	};
}