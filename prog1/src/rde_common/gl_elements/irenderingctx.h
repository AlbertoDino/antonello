#pragma once
#include "winobj.h"

namespace oglElements {

	class IRenderingCtx {
	public:
		virtual void init(oglElements::WinObj* window) = 0;
		virtual void render() const = 0;
		virtual void end() = 0;

		int32 getContextId() const;
	protected: 
		int32 contextId;
	};

}