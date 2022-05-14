#pragma once

namespace oglElements {

#define MAX_QUEUE_TASK 264

	class TaskQueue {	
	public:

		TaskQueue(int32 capacity= MAX_QUEUE_TASK);

		~TaskQueue();

		Task* popTaskFromQueue();

		bool8 addTaskToQueue(Task* task);
		
	private:

		int32 nextIndex(int32 i);

		Task** queue;
		int32 maxCapacity;
		int32 insertIndex;
		int32 takeIndex;
	};


}