#pragma once
#include "task.h"
#include "taskqueue.h"
#include "taskexecuter.h"
#include "iinteractivesurface.h"

namespace oglElements {



	class TaskExecuter {
	public:

		TaskExecuter();
		~TaskExecuter();

		void init(oglElements::TaskQueue* q);
		void setSurface(oglElements::IInteractiveSurface* w);
		
		void loop(float32 elapse);

	private:

		void newActiveTask(oglElements::Task* task);
		void removeTask(oglElements::Task* task);
		void processTask(oglElements::Task* task, float32 elapse);	
		void clearCompletedTasks();

		oglElements::TaskQueue *queue;
		oglElements::IInteractiveSurface *world;

		std::vector<oglElements::Task*> activeTasks;		
		std::vector<oglElements::Task*> completedTasks;

	};
}