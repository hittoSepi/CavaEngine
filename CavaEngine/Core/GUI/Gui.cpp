#include "Core/GUI/Gui.h"
#include "Core/Application/Application.h"
#include "Core/Window/Window.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace Cava
{

	
	Gui::Gui(Application* app):
		app(app)
	{
		LogInfo("");
		options = app->getOptions().guiOptions;
		
		// Setup Dear ImGui context
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsDark();

		//	ImGui::ShowDemoWindow()

		ImGui_ImplGlfw_InitForOpenGL(app->getWindow()->getGLFWwindow(), false);
		ImGui_ImplOpenGL3_Init("#version 150");
	}


	void Gui::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if(options.showPerformanceCounters)
			showPerformanceCounters();
		
		app->getRenderer()->renderGUI();
		ImGui::Render();
	}

	
	void Gui::render()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	void Gui::quit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	
	void Gui::showPerformanceCounters()
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(225, 36), ImGuiCond_Always);
		ImGui::Begin("Performance", nullptr, (int)WindowType::StaticNoTitle);
			ImGui::AlignTextToFramePadding();
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
			ImGui::SameLine();
			ImGui::AlignTextToFramePadding();
			ImGui::Text("FrameTime: %.1f ms", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::End();
	}

	
}