#pragma once
#include "scenenode.h"

namespace oglElements {

	enum eCameraMode {
		CameraFree,
		Camera3rd,
	};

	class CameraScene : public SceneNode {
	public:
		CameraScene();
		~CameraScene();
	};

	class ICamera {
	public:

		virtual void setProjection(int32 screenWidth, int32 screenHeight) = 0;
		virtual float32 move(const func::CVector3f& mov, float32 elapsedTimeSec) = 0;
		virtual void rotate(const func::CVector3f& vector, float32 elapsedTimeSec) = 0;
		virtual void updateViewMatrix() = 0;

	};

}