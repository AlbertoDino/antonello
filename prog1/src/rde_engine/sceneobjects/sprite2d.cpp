#include <rde_common/lib.h>
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "sprite2d.h"

namespace sceneobjs {

    Sprite2D::Sprite2D():
        speed (0.1)
    {
        size = 1;
        pRender = new oglElements::DrawSprite2D();
        *((oglElements::DrawArrayObjectWithTexture*) pRender) = *rex::Rectangle::getModel();
    }


    void Sprite2D::updateSpriteFrame(float32 elaps)
    {
        CMatrix4f32 scale, translate;

        scale.Scale(size.data);
        translate.Translate(position.data);

        pSceneNode->view = scale * translate;

        ((oglElements::DrawSprite2D*)pRender)->updateAnimationFrame(speed, elaps);
    }

    void Sprite2D::add2scene()
    {

        oglElements::ShaderContext* rendering = (oglElements::ShaderContext*)api::getRenderingContext(api::eRenderingContext::ShaderFlatTextureCtx);
        
        if (!rendering)
            throwError("Cannot find shaderFlat layout.");

        oglElements::DrawSprite2D* draw = (oglElements::DrawSprite2D*)pRender;

        shaderValues = rendering->shader;
        shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_M4f, "mvpMatrix", &pSceneNode->worldmvp.data);
        shaderValues.add((oglElements::UniformLocationFunc)oglElements::UniformLocation_V1i, "sampler", &draw->textureObject.unit);

        rendering->add2Context(this);
    }

    oglElements::DrawSprite2D* Sprite2D::getSpriteRendering()
    {
        return (oglElements::DrawSprite2D*)pRender;
    }

}