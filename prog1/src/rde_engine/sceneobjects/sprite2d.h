#pragma once


namespace sceneobjs {

	class DrawSprite2D : public oglElements::RenderingElement {
	public:

		DrawSprite2D();
		~DrawSprite2D();

		void setTextureByFilename(const std::string& filename);

		void addAnimation(const std::string& filename, oglElements::AnimationType aniType);

		// Animations have to be created first via addAnimation function
		void playAnimation(oglElements::AnimationType aniType);

		void updateAnimationFrame(float32 animationSpeed, float32 delta);

		virtual void render() const override;

		oglElements::gl_vertexObject	vertexObject;
		oglElements::gl_to				textureObject;
	private:	
		int32 texture_width;
		int32 texture_height;
		oglElements::Draw2DAnimation* currentAnimation;
		std::vector<oglElements::Draw2DAnimation*> animations;
	};

	class Sprite2D : public oglElements::GameObject {
	public:
		Sprite2D();

		void updateSpriteFrame(float32 elaps);
		void add2scene();

		bool8 isFacingRightX();
		bool8 isFacingLeftX();

		void runRightX(float32 elapse);
		void runLefttX(float32 elapse);
		oglElements::Task* createJump();

		CVector3f		vJump;				//jump vector
		float32			jumpSpeed;			//jump speed
		float32			animationSpeed;		//animation frame speed
		
		DrawSprite2D	*render;
	
	};

}