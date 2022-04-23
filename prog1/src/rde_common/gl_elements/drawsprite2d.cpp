#include <rdecommon.h>
#include "gltypes.h"
#include "draw2danimation.h"
#include "drawobjects.h"
#include "texture.h"
#include "drawsprite2d.h"

namespace oglElements {



	DrawSprite2D::DrawSprite2D()
	{
	}

	DrawSprite2D::~DrawSprite2D()
	{
	}

	void DrawSprite2D::setTextureByFilename(const std::string& filename)
	{	
		Texture tex;
		const ImageDetail & det = tex.createByFilename(textureObject, GL_TEXTURE_2D, filename);
		texture_width = det.width;
		texture_height = det.height;
	}

	void DrawSprite2D::addAnimation(const std::string& filename, AnimationType aniType)
	{
		auto anim = new Draw2DAnimation();

		anim->loadAnimationfromFile(filename, aniType);

		animations.push_back(anim);
	}


	void DrawSprite2D::playAnimation(AnimationType aniType)
	{
		currentAnimation = 0;
		for (auto anim : animations) {
			if (anim->getAnimationType() == aniType) {
				currentAnimation = anim;
				return;
			}
		}
	}

	void DrawSprite2D::updateAnimationFrame(float32 speed, float32 delta)
	{
		if (currentAnimation)
			currentAnimation->updateFrameUniform(texture_width, texture_height, vertexObject, speed, delta);
	}

}