#pragma once
#include "sceneunitnode.h"
#include "renderingelement.h"

namespace oglElements {


	class SceneShaderObject {
	public:
		SceneShaderObject();
		~SceneShaderObject();

		ShaderUniforms		shaderValues; // shader update
		SceneUnitNode		*pSceneNode;  // position/projection matrixes
		RenderingElement	*pRender;     // drawing calls
		
		void render() const;

		SceneShaderObject	*pNext, *pLast;

	};

}