#pragma once
#include <rde_common/lib.h>

namespace win {

	class TaskLinearJump : public oglElements::Task {
	public:

		CVector3f currentJumpVector;

		void updateView(float32 elapse, oglElements::InteractionRequest* out_request);

		void processResponse(const oglElements::InteractionResponse* response);
	};

	class TaskExecuter {
	public:

		TaskExecuter();

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