#include <rdecommon.h>
#include "..\math\mathcommon.h"
#include "scenenode.h"

namespace oglElements {

	SceneNode::SceneNode()
		: pParent {0}, pNextNode{ 0 }, pPrevnode {0}
		, pFirstChild{ 0 }, pLastChild{ 0 }
		, childCount (0)
	{
	}

	SceneNode::~SceneNode()
	{
		if (pNextNode)
			delete pNextNode;
		pNextNode = 0;

		if(pFirstChild)
			delete pFirstChild;

		pFirstChild = 0;
	}


	int32 SceneNode::count() const
	{
		return childCount;
	}

	void SceneNode::addChild(SceneNode* node) {
		if (!node) return;

		if (!pFirstChild)
			pFirstChild = node;
		else
			pLastChild->pNextNode = node;

		pLastChild = node;
		node->pParent = this;

		childCount++;
	}

	void SceneNode::setDebugName(std::string name) {
		__debugName = name;
	}
}