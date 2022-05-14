#include <rde_common/lib.h>
#include "linearsurface.h"

namespace win {

	LinearSurface::LinearSurface() :
		gravityAcceleration(3.9)
	{
		gravityDirection = { 0,-1,0 };

	}

	void LinearSurface::getInteractionResponse(
		const oglElements::InteractionRequest& request
		, oglElements::InteractionResponse& out_response
		, float32 elapse) const
	{
		// origin + vmoment
		CVector3f destination = request.origin + request.vMovement * elapse;


		// check heright
		float32 surfaceHeight = getHeight(destination[0], destination[2]);

		out_response.destination = destination;

		if (destination[1] > surfaceHeight) {
			//apply gravity

			//gravity vector
			CVector3f gravity = gravityDirection * gravityAcceleration * elapse;
			

			CVector3f finalMovement = request.vMovement + gravity;


			out_response.destination = request.origin + finalMovement;
			out_response.vMovement = finalMovement;
		}
		else
		{
			out_response.destination[1] = surfaceHeight;
			out_response.interactionCompleted = true;
		}
	}


	float32 LinearSurface::getHeight(float32 x, float32 z) const
	{
		return 0;
	}
}