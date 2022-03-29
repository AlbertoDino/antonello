#pragma once
#include "shaderuniforms.h"

namespace oglElements {

	class RenderingElement
	{
	public:
		RenderingElement();

		virtual void render() const = 0;

	};

}