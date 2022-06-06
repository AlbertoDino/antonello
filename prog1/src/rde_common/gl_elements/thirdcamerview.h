#pragma once

#include "..\math\local.h"
#include "frustum.h"
#include "gameobject.h"
#include "scenenode.h"

using namespace func;

namespace oglElements {

	class ThirdCameraView : public ICamera {

	public:
		ThirdCameraView();
		~ThirdCameraView();

		void    setCameraScene(CameraScene* c);
		void    setObjectToFollow(GameObject* t);

		void	setProjection(int32 screenWidth, int32 screenHeight);
		float32 move(const func::CVector3f& mov, float32 elapsedTimeSec);
		void	rotate(const func::CVector3f& vector, float32 elapsedTimeSec);
		void	updateViewMatrix();

		const CVector3f& getDirection() const;
		const CVector3f& getRotation() const;
		const CVector3f& getPosition() const;

		CVector3f vDistance;
		float32 fovx, znear, zfar;
		Quaternion quaternion;

	private:

		void	updateFrustum();

		CVector3f position;
		CVector3f offset;
		CVector3f direction;
		CVector3f rotation;
		std::unique_ptr<Frustum> frustum;
		CameraScene* cameraNode;
		GameObject* target;
	};

}