#pragma once
#include "..\math\local.h"

namespace oglElements {

	class SceneNode
	{
	public:

		SceneNode();
		~SceneNode();		
		
		func::CMatrix4f32 view;
		func::CMatrix4f32 projection;
		func::CMatrix3f32 normal;
		func::CMatrix4f32 worldview;
		func::CMatrix4f32 worldprojection;
		func::CMatrix4f32 worldmvp;

		int32 count() const;
		void addChild(SceneNode* node);
		void setDebugName(std::string name);

		SceneNode* pParent;
		SceneNode *pNextNode, *pPrevnode; 
		SceneNode *pFirstChild, *pLastChild;  

		
	private:
		int32 childCount;

		//To remove in Release
		std::string __debugName;
	};
}

