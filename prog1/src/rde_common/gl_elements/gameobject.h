#pragma once
#include "scenenode.h"
#include "renderingelement.h"
#include "..\math\local.h"

namespace oglElements {


	class GameObjectData {
	public:

		GameObjectData();

		float32				speed;
		func::CVector3f		scale;
		func::CVector3f		position;
		func::CVector3f		positionOffset;
		func::CVector3f		direction;
		func::CVector3f		rotation;		
		func::Quaternion	orientation;
		std::string			name;
		uint32				id;
	};

	/*
	GameObject represents an object in scene 
	it has all the components needed for being drawn in the screen
	*/
	class GameObject {
	public:
		GameObject();
		~GameObject();

		GameObjectData		*data;
		ShaderUniforms		shaderValues; // shader uniform links		
		RenderingElement	*refRender;   // Draw rappresentation

		SceneNode* getSceneNode();

		void render() const;

		void updateMatrixes();
	protected:
		SceneNode* pSceneNode;  // view/projection matrixes
	};

}