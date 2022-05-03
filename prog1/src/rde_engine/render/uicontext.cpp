#include <rde_common/lib.h>
#include "uicontext.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace render {

	UIContext::UIContext(int32 rndContextId)
	{
		contextId = rndContextId;
	}
	
	UIContext::~UIContext()
	{
		end();
	}

	void UIContext::init(oglElements::WinObj* window)
	{
		const char* glsl_version = "#version 410";

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->glWindowHandler, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
	}


	void UIContext::render() const
	{
		if (uiComponents.empty()) 
			return;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		for (auto const& uiComp : std::as_const(uiComponents)) {
			uiComp->render();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	void UIContext::end()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

}