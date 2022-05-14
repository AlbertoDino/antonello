#pragma once
#include "..\math\local.h"

using namespace func;

namespace oglElements {

	class LinearMovement {
	public:

		float32 move(const CVector3f & origin
			, const CVector3f & vDirectionMov
			, CVector3f& finalPosition
			, float32 defaultSpeed
			, float32 elapse);

		void rotate(Quaternion& quaternion
			, float32 headingDgr, float32 pitcDgr
			, float32 rollDgr
			, Quaternion& finalRotation
			, float32 elapse);
	};

}