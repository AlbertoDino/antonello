#pragma once
#include <rde_common/lib.h>
#include <rde_engine/lib.h>
#include "gameapi.h"
#include <functional>

class IGameSession {
public:
	IGameSession() : onChangeSession(0) {

	}

	virtual void loop(float32 elapse) = 0;

	virtual void OnKey(int key, int scancode, int action, int mods) = 0;
	virtual void OnMouseScroll(double xoffset, double yoffset) = 0;
	virtual void OnWindowSizeChange(int width, int height) = 0;
	virtual void OnWindowClose() = 0;
	virtual void OnPositionCursorChange(double xpos, double ypos) = 0;

	virtual void Show() = 0;
	virtual void Hide() = 0;

	void RaisingChangeSession(eGameSession session) {
		if (onChangeSession)
			onChangeSession(session);
	}

	void setRaiseSessionCallback(const std::function<void(eGameSession)>& callback) {
		onChangeSession = callback;
	}

private:
	std::function<void(eGameSession)> onChangeSession;
};