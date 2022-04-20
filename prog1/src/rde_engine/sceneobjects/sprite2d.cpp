#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "sprite2d.h"

namespace sceneobjs {

    Sprite2D::Sprite2D()
    {
        pRender = new oglElements::DrawSprite2D();
        rex::Rectangle::createRectangle((oglElements::DrawArrayObjectWithTexture *)pRender);

        oglElements::DrawSprite2D* draw = (oglElements::DrawSprite2D*)pRender;

        draw->setTexture("assets/textures/sprite/spritesheet.png");
        draw->addAnimation("assets/textures/sprite/Run.txt", oglElements::AnimationType::Run);
        draw->playAnimation(oglElements::AnimationType::Run);
        currentAnimation = oglElements::AnimationType::Run;
    }

    void Sprite2D::updateFrame(float32 elaps)
    {
        ((oglElements::DrawSprite2D*)pRender)->updateAnimationFrame(0.1, elaps);
    }

    void Sprite2D::add2scene()
    {
        oglElements::DrawSprite2D* draw = (oglElements::DrawSprite2D*)pRender;
        oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderFlatTextureCtx);
        
        if (!rendering)
            throwError("Cannot find shaderFlat layout.");

        shaderValues = rendering->shader;
        shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
        shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, "sampler", &draw->textureObject.unit);

        rendering->add2Context(this);
    }

}