#pragma once
#include "..\math\mathcommon.h"

namespace oglElements {

	class SceneUnitNode
	{
	public:

		SceneUnitNode();
		~SceneUnitNode();

		
		
		func::CMatrix4f32 view;
		func::CMatrix4f32 projection;
		func::CMatrix4f32 normal;
		func::CMatrix4f32 worldview;
		func::CMatrix4f32 worldprojection;
		func::CMatrix4f32 worldmvp;

		int32 count() const;
		void addChild(SceneUnitNode* node);
		void setDebugName(std::string name);

		SceneUnitNode* pParent;
		SceneUnitNode *pNextNode, *pPrevnode; 
		SceneUnitNode *pFirstChild, *pLastChild;  

		
	private:
		int32 childCount;

		//To remove in Release
		std::string __debugName;
	};
}

