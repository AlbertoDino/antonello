#pragma once

namespace oglElements {

	class InteractionResponse {
	public:

		InteractionResponse();

		func::CVector3f vMovement;
		func::CVector3f	destination;
		bool8 interactionCompleted;
	};

	class InteractionRequest {
	public:

		//direction and lenght is the power
		func::CVector3f vMovement;

		// starting position
		func::CVector3f	origin;
	};

	class IInteractiveSurface {

	public:
		virtual ~IInteractiveSurface();

		virtual void getInteractionResponse(
			const oglElements::InteractionRequest& request
			, oglElements::InteractionResponse& out_response
			, float32 elapse) const = 0;

	};

}