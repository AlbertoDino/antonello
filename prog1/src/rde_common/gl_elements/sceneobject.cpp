#include <rdecommon.h>
#include "renderingelement.h"
#include "sceneobject.h"

namespace oglElements {

	SceneObject::SceneObject() :
		pSceneNode(new SceneNode()), refRender(0)
	{
	}

	SceneObject::~SceneObject()
	{
		if (pSceneNode)
			delete pSceneNode;
		pSceneNode = 0;
	}

	SceneNode* SceneObject::getSceneNode()
	{
		return pSceneNode;
	}

	void SceneObject::render() const
	{
		shaderValues.updateUniforms();
		if (refRender) {
			refRender->render();
		}
	}
}