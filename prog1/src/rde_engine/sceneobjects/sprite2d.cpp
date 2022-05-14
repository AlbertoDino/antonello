#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "sprite2d.h"

namespace sceneobjs {

	DrawSprite2D::DrawSprite2D()
	{
	}

	DrawSprite2D::~DrawSprite2D()
	{
	}

	void DrawSprite2D::setTextureByFilename(const std::string& filename)
	{
		oglElements::Texture tex;

		const oglElements::ImageDetail& det = tex.loadImageByFilename(filename);
		tex.create(&textureObject, GL_TEXTURE_2D, 0);
		tex.bind();
		tex.setFiltering(GL_LINEAR, GL_LINEAR);
		tex.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
		tex.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
		tex.generateMipmap();
		tex.save();
		tex.unbind();

		texture_width = det.width;
		texture_height = det.height;
	}

	void DrawSprite2D::addAnimation(const std::string& filename, oglElements::AnimationType aniType)
	{
		auto anim = new oglElements::Draw2DAnimation();

		anim->loadAnimationfromFile(filename, aniType);

		animations.push_back(anim);
	}


	void DrawSprite2D::playAnimation(oglElements::AnimationType aniType)
	{
		currentAnimation = 0;
		for (auto anim : animations) {
			if (anim->getAnimationType() == aniType) {
				currentAnimation = anim;
				return;
			}
		}
	}

	void DrawSprite2D::updateAnimationFrame(float32 animationSpeed, float32 delta)
	{
		if (currentAnimation)
			currentAnimation->updateFrameUniform(texture_width, texture_height, vertexObject, animationSpeed, delta);
	}

	void DrawSprite2D::render() const
	{
		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0 + textureObject.unit);
		glBindTexture(textureObject.target, textureObject.uId);

		glBindVertexArray(vertexObject.VAO);
		glDrawArrays(vertexObject.drawMode, 0, vertexObject.count);
		glBindVertexArray(0);

		glBindTexture(textureObject.target, 0);
		glActiveTexture(0);

		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
	}

	//-----------------------------------------------------------------

	Sprite2D::Sprite2D() :
		animationSpeed(0.05),
		jumpSpeed(1),
		vJump{ 0.25,1.0,0 }
	{
		refRender = render = new DrawSprite2D();
		render->vertexObject = rex::Rectangle::getModel();
	}


	void Sprite2D::updateSpriteFrame(float32 elaps)
	{
		updateMatrixes();
		render->updateAnimationFrame(animationSpeed, elaps);
	}

	void Sprite2D::add2scene()
	{

		oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderFlatTexture);

		if (!rendering)
			throwError("Cannot find shaderFlat layout.");


		shaderValues = rendering->shader;
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
		shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, "sampler", &render->textureObject.unit);

		rendering->add2Context(this);
	}


	bool8 Sprite2D::isFacingRightX() {
		return func::IsEqual(data->orientation.y, 0);
	}

	bool8 Sprite2D::isFacingLeftX()
	{
		return func::IsEqual(data->orientation.y, 1);
	}

	void Sprite2D::runRightX(float32 elapse)
	{
		tracelog("Sprite running right X");
		if (!isFacingRightX()) {
			data->orientation.Rotate(CVector3f{ 180,0,0 }, 1);
			updateMatrixes();
		}

		CVector3f vDirection = data->direction;
		oglElements::FreePhysic physic(this);

		CVector3f moveRight;
		moveRight.Cross(World::World_Y_Axis, vDirection * data->defaultSpeed);

		physic.move(moveRight, elapse);
		//updateMatrixes();

		render->playAnimation(oglElements::AnimationType::Run);
	}

	void Sprite2D::runLefttX(float32 elapse)
	{
		tracelog("Sprite running left X");
		if (!isFacingLeftX()) {
			data->orientation.Rotate(CVector3f{ -180,0,0 }, 1);
			updateMatrixes();
		}

		CVector3f vDirection = data->direction;

		oglElements::FreePhysic physic(this);

		CVector3f moveLeft;
		moveLeft.Cross(World::World_Y_Axis, vDirection * data->defaultSpeed);

		physic.move(moveLeft, elapse);
		//updateMatrixes();

		render->playAnimation(oglElements::AnimationType::Run);

	}

	oglElements::Task* Sprite2D::createJump()
	{
		int32 direction2d = isFacingLeftX() ? -1 : 1;

		auto jump = new oglElements::TaskLinearJump();
		jump->gameObj = this;
		jump->currentJumpVector = vJump;
		jump->currentJumpVector[0] *= direction2d;
		jump->currentJumpVector *= jumpSpeed;

		jump->onComplete(
			[this](oglElements::Task* t) {
				auto sprite = (sceneobjs::Sprite2D*)t->gameObj;
				sprite->render->playAnimation(oglElements::AnimationType::Idle);
			}
		);

		render->playAnimation(oglElements::AnimationType::Jumps);
		return jump;
	}

}