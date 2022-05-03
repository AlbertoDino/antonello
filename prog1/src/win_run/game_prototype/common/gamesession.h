#pragma once
#include <rde_common/lib.h>
#include <rde_engine/lib.h>

class IGameSession {
public:


	virtual void loop(float32 elapse) = 0;

};