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
		
		RenderingElement	*refRender;   // drawing calls

		SceneNode* getSceneNode();

		void render() const;

	protected:
		SceneNode* pSceneNode;  // position/projection matrixes
	};

}