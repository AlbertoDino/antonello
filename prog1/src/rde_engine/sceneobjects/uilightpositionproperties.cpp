#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "uilightpositionproperties.h"

namespace sceneobjs {



    UILightPositionProperties::UILightPositionProperties() :
        light(0)
    {
    }

    void UILightPositionProperties::setLight(LightPosition* _light)
    {
        light = _light;
    }

    void UILightPositionProperties::render()
    {
        if (!light) return;

        ImGui::Begin("Position Properties");
        ImGui::ColorEdit3("ambient", light->ambientColor.data);
        ImGui::ColorEdit3("diffuse", light->diffuseColor.data);
        ImGui::SliderFloat3("position", light->lightPosition.data, -100, +100);
        ImGui::SliderFloat("power", &light->lightPower, -100, +100);
        ImGui::End();

    }

}