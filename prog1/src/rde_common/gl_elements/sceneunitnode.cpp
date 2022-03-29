#include <rdecommon.h>
#include "..\math\mathcommon.h"
#include "sceneunitnode.h"

namespace oglElements {

	SceneUnitNode::SceneUnitNode()
		: pParent {0}, pNextNode{ 0 }, pPrevnode {0}
		, pFirstChild{ 0 }, pLastChild{ 0 }
		, childCount (0)
	{
	}

	SceneUnitNode::~SceneUnitNode()
	{
		if (pNextNode)
			delete pNextNode;
		pNextNode = 0;

		if(pFirstChild)
			delete pFirstChild;

		pFirstChild = 0;
	}


	int32 SceneUnitNode::count() const
	{
		return childCount;
	}

	void SceneUnitNode::addChild(SceneUnitNode* node) {
		if (!node) return;

		if (!pFirstChild)
			pFirstChild = node;
		else
			pLastChild->pNextNode = node;

		pLastChild = node;
		node->pParent = this;

		childCount++;
	}

	void SceneUnitNode::setDebugName(std::string name) {
		__debugName = name;
	}
}