#include <rdecommon.h>
#include "gameobject.h"
#include "linearmovent.h"
#include "freephysic.h"

using namespace func;

namespace oglElements {

	FreePhysic::FreePhysic(GameObject* obj)
		: game(obj)
	{
	}

	float32 FreePhysic::move(const CVector3f vMovement, float32 elapse)
	{
		LinearMovement lm;
		CVector3f vNorm(vMovement);
		vNorm.Normalize();
		return lm.move(game->data->position, vNorm, game->data->position, game->data->defaultSpeed, elapse);
	}

	void FreePhysic::rotate(float32 headingDgr, float32 pitchDgr, float32 rollDgr, float32 elapse)
	{
		Quaternion finalOrientation;

		LinearMovement lm;
		lm.rotate(game->data->orientation,
			headingDgr,
			pitchDgr,
			rollDgr,
			finalOrientation,
			elapse);

		game->data->orientation = finalOrientation;
	}

}