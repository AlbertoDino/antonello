#include <rdecommon.h>
#include "renderingelement.h"
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

}