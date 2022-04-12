#pragma once
#include <functional>

namespace render {

	enum class eMousePickingMethod : int32 {

		eMouseNone = 0,
		eMouseSinglePoint = 1,
		eMouseRectArea = 2,

	};


	class PixelReadContext {
	public:
		PixelReadContext();
		~PixelReadContext();

		virtual void resize(oglElements::WinObj* window);

		void useShader() const;
		void add2Context(oglElements::SceneObject* sceneShaderObject);
		void setOnSelected(const std::function<void(uint32)>& callback);
		void setSelectionByMousePosition(const Coord2i& mousePosition);
		
		virtual void render() const;
		virtual void end();

		oglElements::ShaderUniforms shader;

		void evaluate();
	private:
		void evalByMousePosition();

		std::function<void(uint32)> onSelected;

		eMousePickingMethod		mouseSelectionType;
		int32					screenHeight, screenwidth;
		Rectl					pixelAreaToRead;
		Vector4b				*pixelFrameBuffer;
		oglElements::WinObj		*winObj;
		std::vector<oglElements::SceneObject*> shaderObjects;
	};
}