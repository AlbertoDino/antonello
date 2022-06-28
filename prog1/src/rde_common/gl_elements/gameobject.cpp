#include <rdecommon.h>
#include "renderingelement.h"
#include "settingfile.h"
#include "gameobject.h"

namespace oglElements {


	GameObjectData::GameObjectData() : 
		scale			({ 1,1,1 }),
		position		({ 0,0,0 }),
		positionOffset	({ 0,0,0 }),
		defaultSpeed			(0.1),
		currentSpeed	(0.0)
	{
		id = func::CreateIdFromPointer(this);
		name = "gameobj";
	}

	const func::CVector3f& GameObjectData::getPosition()
	{
		return position + positionOffset;
	}

	GameObject::GameObject() :
		pSceneNode(new SceneNode()), 
		refRender(0),
		data(new GameObjectData())
	{
		settingList = {
			oglElements::ConfigRecord{"name",oglElements::eConfigType::eString, &data->name },
			oglElements::ConfigRecord{"defaultspeed",oglElements::eConfigType::eFloat32,&data->defaultSpeed },
			oglElements::ConfigRecord{"scale",oglElements::eConfigType::eVector3f,data->scale.data },
			oglElements::ConfigRecord{"position",oglElements::eConfigType::eVector3f,data->position.data },
			oglElements::ConfigRecord{"positionoffset",oglElements::eConfigType::eVector3f,data->positionOffset.data },
		};

	}

	GameObject::~GameObject()
	{
		if (pSceneNode)
			delete pSceneNode;
		pSceneNode = 0;

		if (data)
			delete data;
		data = 0;
	}

	SceneNode* GameObject::getSceneNode()
	{
		return pSceneNode;
	}

	void GameObject::render() const
	{
		shaderValues.updateUniforms();
		if (refRender) {
			refRender->render();
		}
	}

	void GameObject::updateMatrixes()
	{
		func::CMatrix4f32					viewmatrix;
		func::CMatrix4f32					trans,scaling, M;

		auto finalPosition = data->getPosition();

		//Rotation
		//// Matrix has no translation information and is
		//// transposed.... (rows instead of columns)
		data->orientation.ToMatrix4(viewmatrix);

		data->direction[0] = viewmatrix.get(0, 2);
		data->direction[1] = viewmatrix.get(1, 2);
		data->direction[2] = viewmatrix.get(2, 2);

		data->direction.Normalize();

		data->rotation[0] = func::RadiantToDegree(atan2(-viewmatrix.get(1, 2), viewmatrix.get(1, 1)));
		data->rotation[1] = func::RadiantToDegree(atan2(-viewmatrix.get(2, 0), viewmatrix.get(0, 0)));// fino a +/-180
		data->rotation[2] = 0.0f;

		//Translation
		trans.Translate(finalPosition.data);

		// Scaling
		scaling.Scale(data->scale.data);

		pSceneNode->view = trans * scaling * viewmatrix;
	}

	void GameObject::setConfigFile(const std::string& filename)
	{
		configFile = filename;
	}

	void GameObject::loadSettingsFromFile()
	{
		if (configFile.empty()) {
			tracelog("Cannot load setting - config file not set");
			return;
		}

		oglElements::SettingFile f;
		f.setSettings(settingList);
		f.load(configFile);
	}

	void GameObject::saveSettingsToFile()
	{
		if (configFile.empty()) {
			tracelog("Cannot save setting - config file not set");
			return;
		}

		tracelog(format("Settings saved to file [%s]", configFile.c_str()));
		oglElements::SettingFile f;
		f.setSettings(settingList);
		f.save(configFile);
	}

}