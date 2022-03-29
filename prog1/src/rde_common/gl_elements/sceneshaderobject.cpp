#include <rdecommon.h>
#include "renderingelement.h"
#include "sceneunitnode.h"
#include "sceneshaderobject.h"

namespace oglElements {

	SceneShaderObject::SceneShaderObject() :
		pSceneNode(new SceneUnitNode()), pRender(0), pNext(0), pLast(0)
	{
	}

	SceneShaderObject::~SceneShaderObject()
	{
		if (pSceneNode)
			delete pSceneNode;
		pSceneNode = 0;

		if (pRender)
			delete pRender;
		pRender = 0;
	}

	void SceneShaderObject::render() const
	{
		shaderValues.updateUniforms();
		if (pRender) {
			pRender->render();
		}
	}
}