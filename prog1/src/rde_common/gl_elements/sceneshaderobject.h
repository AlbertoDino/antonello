#pragma once
#include "sceneunitnode.h"
#include "renderingelement.h"

namespace oglElements {

	/*
	SceneShaderObject represents an object with all the data for being drawn in the scene
	*/
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