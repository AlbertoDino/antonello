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
			virtual void updateInteractionRequest(float32 elapse,InteractionRequest * out_request) = 0;

			virtual void processResponse(const InteractionResponse* response) = 0;
						
			void onComplete(std::function<void(Task*)> cb);

			void complete();
	protected:
			int32			id;
			std::function<void(Task*)> onTaskCompletedCallback;

	};


	// This Task represent any linear movent
	// it could represent a linear Jump
	class TaskLinearMovement : public Task {
	public:

		TaskLinearMovement();
		TaskLinearMovement(GameObject* obj);

		func::CVector3f currentMovementVector;

		void updateInteractionRequest(float32 elapse, InteractionRequest* out_request);

		void processResponse(const InteractionResponse* response);
	};

}