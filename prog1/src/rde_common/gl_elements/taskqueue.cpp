#include <rdecommon.h>
#include <functional>
#include "..\math\local.h"
#include "task.h"
#include "taskqueue.h"

namespace oglElements {

	TaskQueue::TaskQueue(int32 capacity) :
		insertIndex(0),
		takeIndex(0),		
		maxCapacity(capacity)
	{
		queue = new Task * [maxCapacity];
	}

	TaskQueue::~TaskQueue()
	{
		delete[] queue;
	}

	Task* TaskQueue::popTaskFromQueue()
	{
		if (takeIndex == insertIndex)
			return 0;

		Task *t = queue[takeIndex];
		
		takeIndex = nextIndex(takeIndex);		

		return t;
	}

	bool8 TaskQueue::addTaskToQueue(Task* task)
	{
		if (nextIndex(insertIndex) == takeIndex)
			return false;

		queue[insertIndex] = task;

		insertIndex = nextIndex(insertIndex);

		return true;
	}

	int32 TaskQueue::nextIndex(int32 i)
	{
		if ((i+1) == maxCapacity) {
			return 0;
		}
		else
			return i+1;
	}
}