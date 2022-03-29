#pragma once
#include <rde_common/lib.h>

namespace win {

	class GameStats {
	public:

		GameStats() : accumElapse(0), fps(0) 
		{
		}

		float32	accumElapse;
		int32   fps;
	};
}