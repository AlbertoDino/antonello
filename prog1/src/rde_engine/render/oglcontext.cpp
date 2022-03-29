#include <rde_common/lib.h>
#include "oglcontext.h"

namespace render {

    OglContext::OglContext() : Window(nullptr)
    {
    }

    bool OglContext::init(oglElements::WinObj* window)
    {
		Window = window;
		if (!glfwInit())
		{
			fprintf(stderr, "Error: GLFW Window couldn't be initialized\n");
			return false;
		}

		// Create the window and store this window as window pointer
		// so that we can use it in callback functions
		auto glWindow = glfwCreateWindow(Window->width, Window->height, Window->title.c_str(), nullptr, nullptr);
		Window->glWindowHandler = glWindow;

		glfwSetWindowUserPointer(glWindow, Window->user_pointer);
		glfwSetKeyCallback(glWindow, Win_On_Key_Callback);
		glfwSetScrollCallback(glWindow, Win_On_Scroll_Callback);
		glfwSetWindowSizeCallback(glWindow, Win_On_Window_Size_Callback);
		glfwSetWindowCloseCallback(glWindow, Win_On_Window_close_callback);		
		glfwMakeContextCurrent(glWindow);
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(glWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		glfwSetCursorPosCallback(glWindow, Win_On_Cursor_callback);

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		return true;
    }

    void OglContext::pre_render()
    {
		glViewport(0, 0, Window->width, Window->height);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
	}

	void OglContext::post_render()
	{
		glfwSwapBuffers((GLFWwindow*)Window->glWindowHandler);
	}

	void OglContext::end()
	{
		glfwDestroyWindow((GLFWwindow*)Window->glWindowHandler);
		glfwTerminate();
	}
}
