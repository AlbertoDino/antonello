#include <rdecommon.h>
#include "renderingelement.h"
#include "sceneobject.h"

namespace oglElements {

	SceneObject::SceneObject() :
		pSceneNode(new SceneNode()), pRender(0), pNext(0), pLast(0)
	{
	}

	SceneObject::~SceneObject()
	{
		if (pSceneNode)
			delete pSceneNode;
		pSceneNode = 0;

		if (pRender)
			delete pRender;
		pRender = 0;
	}

	void SceneObject::render() const
	{
		shaderValues.updateUniforms();
		if (pRender) {
			pRender->render();
		}
	}
}