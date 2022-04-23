#pragma once
#include "draw2danimation.h"

namespace oglElements {



	class DrawSprite2D : public DrawArrayObjectWithTexture {
		public:

			DrawSprite2D();
			~DrawSprite2D();

			void setTextureByFilename(const std::string& filename);

			void addAnimation(const std::string& filename, AnimationType aniType);

			// Animations have to be created first via addAnimation function
			void playAnimation(AnimationType aniType);

			void updateAnimationFrame(float32 speed, float32 delta);
	private:
		int32 texture_width;
		int32 texture_height;
		Draw2DAnimation* currentAnimation;
		std::vector<Draw2DAnimation*> animations;
	};

}