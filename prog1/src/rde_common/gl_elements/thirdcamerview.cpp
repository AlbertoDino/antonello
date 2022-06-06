#include <rdecommon.h>
#include "..\math\local.h"
#include <glm/gtx/quaternion.hpp>
#include "shader.h"
#include "renderingelement.h"
#include "frustum.h"
#include "perspective.h"
#include "camera.h"
#include "gameobject.h"
#include "icamera.h"
#include "thirdcamerview.h"

using namespace func;

namespace oglElements {

	ThirdCameraView::ThirdCameraView() : 
		  cameraNode (0)
		, target(0)
		, fovx(CAMERA_FOVX)
		, znear(CAMERA_ZNEAR)
		, zfar(CAMERA_ZFAR)
	{
		position.Set(0);
		offset.Set(0);
		direction.Set(0);
		rotation.Set(0);

		frustum = std::make_unique<Frustum>();

		vDistance = { 0,-1,-10 };
	}

	ThirdCameraView::~ThirdCameraView()
	{
	}

	void ThirdCameraView::setCameraScene(CameraScene* c)
	{
		cameraNode = c;
	}

	void ThirdCameraView::setObjectToFollow(GameObject* t)
	{
		target = t;
	}
	
	void ThirdCameraView::setProjection(int32 screenWidth, int32 screenHeight)
	{
		static Perspective perspective;
		perspective.setFrustum(fovx, float(screenWidth) / float(screenHeight), znear, zfar);
		perspective.getMatrix(cameraNode->projection);
	}

	float32 ThirdCameraView::move(const func::CVector3f& mov, float32 elapsedTimeSec)
	{
		float32 movLength = elapsedTimeSec * 50;
		position[0] -= mov[0] * movLength;
		position[1] -= mov[1] * movLength;
		position[2] -= mov[2] * movLength;
		return movLength;
	}

	void ThirdCameraView::rotate(const func::CVector3f& vector, float32 elapsedTimeSec)
	{
		quaternion.RotateAsCamera(vector, elapsedTimeSec * 50, f_EPSILON);
	}

	void ThirdCameraView::updateViewMatrix()
	{
		CMatrix4f32 viewMatrix, translateMatrix;

		CVector3f targetPosition = target->data->getPosition();
		CVector3f cameraPosition = targetPosition*(-1) + vDistance;

		quaternion.ToMatrix4(viewMatrix);
		direction[0] = -viewMatrix.get(2, 0);
		direction[1] = -viewMatrix.get(2, 1);
		direction[2] = -viewMatrix.get(2, 2);

		rotation[0] = func::RadiantToDegree(atan2(-viewMatrix.get(1, 2), viewMatrix.get(1, 1)));
		rotation[1] = func::RadiantToDegree(atan2(-viewMatrix.get(2, 0), viewMatrix.get(0, 0)));
		rotation[2] = 0.0f;

		translateMatrix.Translate(cameraPosition.data);

		cameraNode->view = viewMatrix * translateMatrix;
		updateFrustum();
	}

	void ThirdCameraView::updateFrustum()
	{
		frustum->calculateFrom(cameraNode->worldview, cameraNode->worldprojection);
	}

	const CVector3f& ThirdCameraView::getDirection() const
	{
		return direction;
	}

	const CVector3f& ThirdCameraView::getRotation() const
	{
		return rotation;
	}

	const CVector3f& ThirdCameraView::getPosition() const
	{
		return position;
	}
}