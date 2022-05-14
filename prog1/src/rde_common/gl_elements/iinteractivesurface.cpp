#include <rdecommon.h>
#include "..\math\local.h"
#include "iinteractivesurface.h"

namespace oglElements {

	IInteractiveSurface::~IInteractiveSurface()
	{
	}

	InteractionResponse::InteractionResponse()
		: interactionCompleted(false)
	{

	}

}