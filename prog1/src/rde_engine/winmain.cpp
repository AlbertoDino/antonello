#include <rde_common/lib.h>
#include "rde_engine/render/local.h"
#include "rde_engine/builtresources/local.h"
#include "rde_engine/header/api.h"
#include "rde_engine/win/local.h"
#include "application.h"
#include "console.h"
#include "winmain.h"

Application *gApp;

void tracelog(std::string msg) {
	gConsole->logDebug(msg);
}

void throwError(std::string msg) {
	MessageBox(NULL, msg.c_str(), _COMPILE_LPCWSTR_"ERROR", MB_OK | MB_ICONEXCLAMATION);
}

std::string	format(const char8* fmt, ...)
{
	static char8 text[TEXT_FORMAT_MAX_SIZE];
	memset(text, 0, sizeof(char8) * TEXT_FORMAT_MAX_SIZE);
	va_list ap;
	va_start(ap, fmt);                              // Parses The String For Variables
	vsprintf(text, fmt, ap);                    // And Converts Symbols To Actual Numbers
	va_end(ap);                                     // Results Are Stored In Text
	return text;
}

void formatExt(std::string* str, const char8* fmt, ...)
{
	static char8 text[TEXT_FORMAT_MAX_SIZE];
	va_list ap;
	va_start(ap, fmt);
	vsprintf(text, fmt, ap);
	va_end(ap);
	*str = text;
}


namespace render {

	void Win_On_Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto pWindow = static_cast<render::WinEventHandler*>(glfwGetWindowUserPointer(window));
		pWindow->OnKey(key, scancode, action, mods);
	}


	void Win_On_Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset) {
		auto pWindow = static_cast<render::WinEventHandler*>(glfwGetWindowUserPointer(window));
		pWindow->OnMouseScroll(xoffset, yoffset);
	}


	void Win_On_Window_Size_Callback(GLFWwindow* window, int width, int height) {
		auto pWindow = static_cast<render::WinEventHandler*>(glfwGetWindowUserPointer(window));
		gApp->resize(width,height);
		pWindow->OnWindowSizeChange(width, height);
	}


	void Win_On_Window_close_callback(GLFWwindow* window) {
		auto pWindow = static_cast<render::WinEventHandler*>(glfwGetWindowUserPointer(window));
		pWindow->OnWindowClose();
	}

	void Win_On_Cursor_callback(GLFWwindow* window, double xpos, double ypos) {
		auto pWindow = static_cast<render::WinEventHandler*>(glfwGetWindowUserPointer(window));
		pWindow->OnPositionCursorChange(xpos,ypos);
	}
}

namespace api {

	uint32 getModelId(void* model) {
		return func::CreateIdFromPointer(model);
	}

	oglElements::IRenderingCtx* getRenderingContext(api::eRenderingContext rndCtxId) {
		for (auto& ctx : gApp->renderingLayouts) {
			if (rndCtxId == ctx->getContextId()) {
				return ctx;
			}
		}
		return 0;
	}

	render::PixelReadContext* getPixelReadContext() {
		return gApp->getPixelReadCtx();
	}

	const oglElements::gl_to& getDefaultTexture() {
		return gApp->textures.at(0);
	}
}

