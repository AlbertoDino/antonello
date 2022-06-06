#pragma once
#include "..\math\local.h"
#include "frustum.h"
#include "scenenode.h"
#include "icamera.h"

using namespace func;

namespace oglElements {

	class Camera : public ICamera {
	public:
		Camera();
		~Camera();

		void	setCameraNode(CameraScene* node);
		void	setOrigin(const CVector3f& vector);
		void	setOffset(const CVector3f& v);
		void    rotate(const CVector3f& vector, float32 elapsedTimeSec);
		float32	move(const CVector3f& mov,float32 elapsedTimeSec);
		void	updateViewMatrix();
		void	setProjection(int32 screenWidth, int32 screenHeight);
		void	reset();
		void	turn90();
		void	turnless90();
		
		CameraScene* getCameraScene();

		const CVector3f& getDirection() const;
		const CVector3f& getRotation() const;		
		const CVector3f& getPosition() const;

		float32 defaultSpeed, rotationSpeed;
		float32 fovx, znear, zfar;

	private:

		void	updateFrustum();

		CVector3f position;
		CVector3f offset;
		CVector3f direction;
		CVector3f rotation;
		Quaternion quaternion;
		std::unique_ptr<Frustum> frustum;
		CameraScene* cameraNode;
	};

	

}