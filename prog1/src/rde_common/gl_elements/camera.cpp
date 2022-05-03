#include <rdecommon.h>
#include "..\math\local.h"
#include <glm/gtx/quaternion.hpp>
#include "shader.h"
#include "renderingelement.h"
#include "frustum.h"
#include "perspective.h"
#include "camera.h"

using namespace func;

namespace oglElements {

	CameraScene::CameraScene() 
	{

	}

	CameraScene::~CameraScene()
	{
	}

	//============================================================

	Camera::Camera() : cameraNode(0)
		, speed(150.0f)
		, rotationSpeed(20.0f)
		, fovx(CAMERA_FOVX)
		, znear(CAMERA_ZNEAR)
		, zfar(CAMERA_ZFAR)
	{
		position.Set(0);
		offset.Set(0);
		direction.Set(0);
		rotation.Set(0);


		frustum = std::make_unique<Frustum>();
		cameraNode = new CameraScene();
	}

	Camera::~Camera()
	{
		if (cameraNode)
			delete cameraNode;
		cameraNode = 0;
	}

	void Camera::setOrigin(const CVector3f& vector)
	{
		position = vector;
	}

	void Camera::setOffset(const CVector3f& v)
	{
		offset = v;
	}

	void Camera::rotateCamera(const CVector3f& vector, float32 elapsedTimeSec)
	{
		quaternion.RotateAsCamera(vector, elapsedTimeSec*rotationSpeed, f_EPSILON);
	}

	float32 Camera::move(const CVector3f& mov, float32 elapsedTimeSec)
	{
		float32 movLength = elapsedTimeSec * speed;
		position[0] -= mov[0] * movLength;
		position[1] -= mov[1] * movLength;
		position[2] -= mov[2] * movLength;
		return movLength;
	}

	void Camera::updateViewMatrix()
	{
		
		CMatrix4f32 viewMatrix, translateMatrix;
		CVector3f realPosition;

		quaternion.ToMatrix4(viewMatrix);
		direction[0] = -viewMatrix.get(2, 0);
		direction[1] = -viewMatrix.get(2, 1);
		direction[2] = -viewMatrix.get(2, 2);

		rotation[0] = func::RadiantToDegree(atan2(-viewMatrix.get(1, 2), viewMatrix.get(1, 1)));
		rotation[1] = func::RadiantToDegree(atan2(-viewMatrix.get(2, 0), viewMatrix.get(0, 0)));
		rotation[2] = 0.0f;

		realPosition = position + offset;
		translateMatrix.Translate(realPosition.data);
		
		cameraNode->view = viewMatrix * translateMatrix;
		updateFrustum();
	}

	void Camera::setProjection(int32 screenWidth, int32 screenHeight)
	{
		static Perspective perspective;
		perspective.setFrustum(fovx, float(screenWidth) / float(screenHeight), znear, zfar);
		perspective.getMatrix(cameraNode->projection);
	}

	void Camera::reset()
	{
		quaternion.setIdentity();
		position.Set(0);
	}

	void Camera::turn90()
	{
		Quaternion rot;
		rot.FromAxisAngle(World::World_Y_Axis, 90);
		quaternion = rot; 
	}

	void Camera::turnless90()
	{
		Quaternion rot;
		rot.FromAxisAngle(World::World_Y_Axis, -90);
		quaternion = rot;
	}

	void Camera::updateFrustum()
	{
		frustum->calculateFrom(cameraNode->worldview, cameraNode->worldprojection);
	}

	const CVector3f& Camera::getDirection() const
	{
		return direction;
	}

	const CVector3f& Camera::getRotation() const
	{
		return rotation;
	}

	CameraScene* Camera::getCameraScene()
	{
		return cameraNode;
	}

	const CVector3f& Camera::getPosition() const
	{
		return position;
	}

}