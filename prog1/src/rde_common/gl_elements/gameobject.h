#pragma once
#include "scenenode.h"
#include "renderingelement.h"
#include "..\math\local.h"
#include "settingfile.h"

namespace oglElements {


	class GameObjectData {
	public:

		GameObjectData();

		float32				currentSpeed; // current speed of the object
		float32				defaultSpeed; // default speed of the object
		func::CVector3f		scale;
		func::CVector3f		position;
		func::CVector3f		positionOffset;
		func::CVector3f		direction;
		func::CVector3f		rotation;		
		func::Quaternion	orientation;
		std::string			name;
		uint32				id;

		const func::CVector3f& getPosition();
	};

	/*
	GameObject represents an object in scene 
	it has all the components needed for being drawn in the screen
	*/
	class GameObject {
	public:
		GameObject();
		virtual ~GameObject();

		GameObjectData		*data;
		ShaderUniforms		shaderValues; // shader uniform links		
		RenderingElement	*refRender;   // Draw rappresentation

		SceneNode* getSceneNode();

		void render() const;

		void updateMatrixes();

		void setConfigFile(const std::string& filename);
		void loadSettingsFromFile();
		void saveSettingsToFile();
	protected:
		SceneNode		*pSceneNode;  // view/projection matrixes
		std::string		configFile;   //configFile for properties	
		std::vector<oglElements::ConfigRecord> settingList;
	};

}