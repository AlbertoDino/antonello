#pragma once

using namespace func;

namespace oglElements {

	class LinearSurface : public IInteractiveSurface {
	public:
		LinearSurface();

		float32   gravityAcceleration;
		CVector3f gravityDirection;
		float32   defaultHeight;

		void setDefaultHeight(float32 height);

		void getInteractionResponse(
			  const InteractionRequest& request
			, InteractionResponse& out_response
			, float32 elapse) const;

		float32 getHeight(float32 x, float32 z) const;
	};

}