#pragma once


namespace win {

	class LinearSurface : public oglElements::IInteractiveSurface {
	public:
		LinearSurface();

		float32   gravityAcceleration;
		CVector3f gravityDirection;

		void getInteractionResponse(
			  const oglElements::InteractionRequest& request
			, oglElements::InteractionResponse& out_response
			, float32 elapse) const;

		float32 getHeight(float32 x, float32 z) const;
	};

}