#pragma once
#include "..\math\local.h"

namespace oglElements {

	enum AnimationType
	{
		None,
		Idle,
		Run,
		Jumps
	};


	class Draw2DAnimation {
	public:
		Draw2DAnimation();

		void loadAnimationfromFile(const std::string& filename, AnimationType type);

		void updateFrameUniform(
			int32 texture_width,
			int32 texture_height, 
			gl_vertexObject &rectangle,
			float32 speed,
			float32 deltatime);

		AnimationType getAnimationType() const;

	private:
		AnimationType animationType;

		double animCursor;
		int32 currentFrameIndex;
		int32 framesCount;
		
		func::CVector4f frameToRender;
		std::vector<func::CVector4f> frames;
	};
}