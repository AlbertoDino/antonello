#pragma once
#include "..\math\local.h"
#include "gameobject.h"

using namespace func;

namespace oglElements {

	class FreePhysic {
	public:
		FreePhysic(GameObject* obj);

		float32 move(const CVector3f vDirectionMov, float32 elapse);

		void rotate(float32 headingDgr
			, float32 pitchDgr
			, float32 rollDgr
			, float32 elapsedTimeSec);

	protected:
		GameObject* game;
	};

}