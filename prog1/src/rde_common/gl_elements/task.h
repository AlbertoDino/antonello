#pragma once
#include <functional>
#include "gameobject.h"
#include "iinteractivesurface.h"

namespace oglElements {

	class Task {
	public:
			Task();			
			
			int32			taskTypeId;
			GameObject*		gameObj;			

			int32 getId() const;

			// Update views and create a interaction request
			virtual void updateView(float32 elapse,InteractionRequest * out_request) = 0;

			virtual void processResponse(const InteractionResponse* response) = 0;
						
			void onComplete(std::function<void(Task*)> cb);

			void complete();
	protected:
			int32			id;
			std::function<void(Task*)> onTaskCompletedCallback;

	};

	class TaskLinearJump : public Task {
	public:

		func::CVector3f currentJumpVector;

		void updateView(float32 elapse, InteractionRequest* out_request);

		void processResponse(const InteractionResponse* response);
	};

}