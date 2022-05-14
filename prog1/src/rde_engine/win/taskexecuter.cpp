#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "rde_engine/sceneobjects/local.h"
#include "taskexecuter.h"

namespace win {

	

	void TaskLinearJump::updateView(float32 elapse, oglElements::InteractionRequest* out_request)
	{
		out_request->origin = gameObj->data->position;
		out_request->vMovement = currentJumpVector;
	}

	void TaskLinearJump::processResponse(const oglElements::InteractionResponse* response)
	{
		gameObj->data->currentSpeed = response->vMovement.Length();
		gameObj->data->position = response->destination;
		currentJumpVector = response->vMovement;
	}

	//--------------------------


	TaskExecuter::TaskExecuter()
	{
	}

	void TaskExecuter::init(oglElements::TaskQueue* q)
	{
		queue = q;
	}

	void TaskExecuter::setSurface(oglElements::IInteractiveSurface* w)
	{
		world = w;
	}

	void TaskExecuter::loop(float32 elapse)
	{
		clearCompletedTasks();

		// get tasks from queue
		oglElements::Task* task = queue->popTaskFromQueue();

		while (task != 0) {
			newActiveTask(task);
			task = queue->popTaskFromQueue();
		}

		// process tasks
		for (auto t : activeTasks)
			processTask(t, elapse);
	}

	void TaskExecuter::newActiveTask(oglElements::Task* t)
	{
		activeTasks.push_back(t);
	}

	void TaskExecuter::removeTask(oglElements::Task* task)
	{
		int32 index = 0;
		bool8 found = false;

		for (; index< activeTasks.size();index++)
		{
			if (found = activeTasks[index]->getId() == task->getId())
				break;
		}

		if (found) {
			completedTasks.push_back(activeTasks.at(index));
			activeTasks.erase(activeTasks.begin() + index);
		}
	}

	void TaskExecuter::processTask(oglElements::Task* task, float32 elapse)
	{
		tracelog(format("Task [%i] processing", task->getId()));
		oglElements::InteractionRequest request;
		oglElements::InteractionResponse response;

		task->updateView(elapse, &request);

		world->getInteractionResponse(request, response,elapse);

		task->processResponse(&response);

		if (response.interactionCompleted) {
			int32 taskId = task->getId();
			task->complete();
			removeTask(task);
			tracelog(format("Task [%i] completed & deleted", taskId));
		}
	}

	void TaskExecuter::clearCompletedTasks() {

		for (int i=0; i < completedTasks.size(); i++) {
			delete completedTasks[i];
		}
		completedTasks.clear();
	}




}

