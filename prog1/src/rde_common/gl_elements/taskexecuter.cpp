#include <rdecommon.h>
#include <functional>
#include "..\math\local.h"
#include "iinteractivesurface.h"
#include "task.h"
#include "taskqueue.h"
#include "taskexecuter.h"

namespace oglElements {

	TaskExecuter::TaskExecuter()
	{
	}

	TaskExecuter::~TaskExecuter()
	{
		clearCompletedTasks();
	}

	void TaskExecuter::init(oglElements::TaskQueue* q)
	{
		queue = q;
	}

	void TaskExecuter::setInteraction(oglElements::IInteractiveSurface* w)
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

		task->updateInteractionRequest(elapse, &request);

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

