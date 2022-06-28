#include <rdecommon.h>
#include <functional>
#include "..\math\local.h"
#include "iinteractivesurface.h"
#include "gameobject.h"
#include "task.h"

namespace oglElements {
	

	Task::Task() : 
		  taskTypeId(0)
		, gameObj(0)
		, onTaskCompletedCallback(0)
	{
		id = func::CreateIdFromPointer(this);
	}

	int32 Task::getId() const 
	{
		return id;
	}

	void Task::onComplete(std::function<void(Task*)> cb)
	{
		onTaskCompletedCallback = cb;
	}

	void Task::complete()
	{
		if (onTaskCompletedCallback)
			onTaskCompletedCallback(this);
	}

	//-----------------------------------------------------

	TaskLinearMovement::TaskLinearMovement() 
	{
	}

	TaskLinearMovement::TaskLinearMovement(GameObject* obj)
	{
		gameObj = obj;
	}

	void TaskLinearMovement::updateInteractionRequest(float32 elapse, InteractionRequest* out_request)
	{
		out_request->origin = gameObj->data->position;
		out_request->vMovement = currentMovementVector;
	}

	void TaskLinearMovement::processResponse(const InteractionResponse* response)
	{
		gameObj->data->currentSpeed = response->vMovement.Length();
		gameObj->data->position = response->destination;
		currentMovementVector = response->vMovement;
	}

}