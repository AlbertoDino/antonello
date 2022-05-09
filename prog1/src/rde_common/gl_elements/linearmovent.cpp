#include <rdecommon.h>
#include "..\math\local.h"
#include "linearmovent.h"

using namespace func;

namespace oglElements {


	float32 LinearMovement::move(const CVector3f& origin
		, const CVector3f& vMovNormal
		, CVector3f& finalPosition
		, float32 speed
		, float32 elapse)
	{
		float32 movLenght = speed * elapse;

		finalPosition[0] = origin[0] + vMovNormal[0] * movLenght;
		finalPosition[1] = origin[1] + vMovNormal[1] * movLenght;
		finalPosition[2] = origin[2] + vMovNormal[2] * movLenght;

		return movLenght;
	}

	void LinearMovement::rotate(Quaternion& quaternion
		, float32 headingDgr
		, float32 pitcDgr
		, float32 rollDgr
		, Quaternion& finalRotation
		, float32 elapse)
	{
		
		CVector3f vRotaion = CVector3f{ headingDgr ,pitcDgr ,rollDgr  };
		finalRotation = quaternion;
		finalRotation.Rotate(vRotaion, elapse);

	}
}