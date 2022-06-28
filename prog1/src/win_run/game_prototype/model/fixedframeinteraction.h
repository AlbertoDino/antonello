#pragma once




class FixedFrameInteraction : public oglElements::IInteractiveSurface
{
public:

	FixedFrameInteraction();
	~FixedFrameInteraction();

	virtual void getInteractionResponse(
		const oglElements::InteractionRequest& request
		, oglElements::InteractionResponse& out_response
		, float32 elapse) const;

	oglElements::LinearSurface surface;


	// Fixed Frame Limit. frameBox[0] left limit. frameBox[1] right limit

	Vector2f frameBox;
};