#pragma once
#include "scenenode.h"
#include "renderingelement.h"

namespace oglElements {

	/*
	SceneObject represents an object in scene 
	it has all the components needed for being drawn in the screen
	*/
	class SceneObject {
	public:
		SceneObject();
		~SceneObject();

		ShaderUniforms		shaderValues; // shader update
		SceneNode			*pSceneNode;  // position/projection matrixes
		RenderingElement	*pRender;     // drawing calls
		
		void render() const;

		SceneObject	*pNext, *pLast;

	};

}