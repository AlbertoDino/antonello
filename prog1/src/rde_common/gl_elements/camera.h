#pragma once
#include "..\math\mathcommon.h"
#include "frustum.h"
#include "scenenode.h"

using namespace func;

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

	class Camera {
	public:
		Camera();
		~Camera();

		void	setOrigin(const CVector3f& vector);
		void	setSpeed(float32 _speed);
		void	setSpeedRotation(float32 _speedRot);
		void	setOffset(const CVector3f& v);
		void    rotateCamera(const CVector3f& vector, float32 elapsedTimeSec);
		float32	move(const CVector3f& mov,float32 elapsedTimeSec);
		void	updateViewMatrix();
		void	setProjection(int32 screenWidth, int32 screenHeight, float32 fovx, float32 znear, float32 zfar);
		void	reset();
		void	turn90();
		void	turnless90();
		
		CameraScene* getCameraScene();

		const CVector3f& getDirection() const;
		const CVector3f& getRotation() const;		
		const CVector3f& getPosition() const;
	private:

		void	updateFrustum();

		float32 speed, rotationSpeed;
		CVector3f position;
		CVector3f offset;
		CVector3f direction;
		CVector3f rotation;
		Quaternion quaternion;
		std::unique_ptr<Frustum> frustum;
		CameraScene* cameraNode;
	};

	

}