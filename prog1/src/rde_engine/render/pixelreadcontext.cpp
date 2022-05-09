#include <rde_common/lib.h>
#include <functional>
#include "pixelreadcontext.h"

namespace render {

	PixelReadContext::PixelReadContext() :
		pixelFrameBuffer(0),
		screenHeight(0),
		screenwidth(0),
		mouseSelectionType(eMousePickingMethod::eMouseNone)
	{
		pixelAreaToRead[0] = 0;
		pixelAreaToRead[1] = 0;
		pixelAreaToRead[2] = 0;
		pixelAreaToRead[3] = 0;
	}

	PixelReadContext::~PixelReadContext()
	{
		if (pixelFrameBuffer)
			delete [] pixelFrameBuffer;
		pixelFrameBuffer = 0;
	}

	void PixelReadContext::resize(oglElements::WinObj* window)
	{
		winObj = window;

		if (screenHeight != window->height || screenwidth != window->width)
		{
			screenHeight = window->height;
			screenwidth  = window->width;

			int32 pixelAreaSize = window->width * window->height;

			if (pixelFrameBuffer)
				delete[] pixelFrameBuffer;

			pixelFrameBuffer = new Vector4b[pixelAreaSize];
			memset(pixelFrameBuffer, 0, sizeof(Vector4b) * pixelAreaSize);
		}
	}

	void PixelReadContext::useShader() const
	{
		shader.useShader();
	}

	void PixelReadContext::add2Context(oglElements::GameObject* sceneShaderObject)
	{
		shaderObjects.push_back(sceneShaderObject);
	}

	void PixelReadContext::setOnSelected(const std::function<void(uint32)>& callback)
	{
		onSelected = callback;
	}

	void PixelReadContext::setSelectionByMousePosition(const Coord2i& mousePosition)
	{
		mouseSelectionType = render::eMousePickingMethod::eMouseSinglePoint;

		pixelAreaToRead[0] = mousePosition[0];
		pixelAreaToRead[1] = screenHeight - mousePosition[1];
		pixelAreaToRead[2] = 1;
		pixelAreaToRead[3] = 1;
	}

	void PixelReadContext::render() const
	{
		if (shaderObjects.size() == 0 || mouseSelectionType == render::eMousePickingMethod::eMouseNone)
			return;

		glViewport(0, 0, screenwidth, screenHeight);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		useShader();
		for (auto const& shaderObject : std::as_const(shaderObjects)) {
			shaderObject->render();
		}

		glReadPixels(pixelAreaToRead[0], pixelAreaToRead[1], pixelAreaToRead[2], pixelAreaToRead[3], GL_RGBA, GL_UNSIGNED_BYTE, pixelFrameBuffer);
	}

	void PixelReadContext::end()
	{
		if (pixelFrameBuffer)
			delete pixelFrameBuffer;
		pixelFrameBuffer = 0;

		shaderObjects.clear();
	}

	void PixelReadContext::evaluate()
	{
		switch (mouseSelectionType)
		{
		case render::eMousePickingMethod::eMouseNone:
			break;
		case render::eMousePickingMethod::eMouseSinglePoint:
			evalByMousePosition();
			break;
		case render::eMousePickingMethod::eMouseRectArea:
			break;
		default:
			break;
		}

	}

	void PixelReadContext::evalByMousePosition()
	{
		uint32 uId = 0;
		int32 rgb = 0;

		uId = (uId << 8) + pixelFrameBuffer[0][0];
		uId = (uId << 8) + pixelFrameBuffer[0][1];
		uId = (uId << 8) + pixelFrameBuffer[0][2];
		rgb = uId;
		uId = (uId << 8) + pixelFrameBuffer[0][3];

		if (rgb && onSelected) {
			onSelected(uId);
		}
	}

}