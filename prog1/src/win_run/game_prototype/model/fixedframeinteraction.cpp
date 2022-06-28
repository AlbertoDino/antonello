#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "fixedframeinteraction.h"


FixedFrameInteraction::FixedFrameInteraction()
{
	frameBox[0] = -10;
	frameBox[1] = 10;
}

FixedFrameInteraction::~FixedFrameInteraction()
{
}

void FixedFrameInteraction::getInteractionResponse(const oglElements::InteractionRequest& request, oglElements::InteractionResponse& out_response, float32 elapse) const
{
	surface.getInteractionResponse(request, out_response, elapse);
	
	
	if (out_response.destination[0] > frameBox[1])
		out_response.destination[0] = frameBox[1];

	if (out_response.destination[0] < frameBox[0])
		out_response.destination[0] = frameBox[0];
	
}
