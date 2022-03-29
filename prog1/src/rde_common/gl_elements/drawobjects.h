#pragma once
#include "renderingelement.h"

namespace oglElements {

	class DrawArrayObject : public RenderingElement {
	public:
		gl_vertexObject vertexObject;

		void render() const override;
	};

	class DrawElementObject : public RenderingElement {
	public:
		gl_vertexObject vertexObject;

		void render() const override;
	};

}