// dear_spdlogger.cpp : Defines the entry point for the application.
//

#include "dear_spdlogger.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <mutex>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "src/dear_sink.h"
#include <string>

using std::cout, std::endl;

int main()
{

	int width = 400;
	int height = 400;
	auto title = "log test";


	const auto ssink = dear_sink_mt();

	spdlog::info("info");
	spdlog::warn("info");
	spdlog::error("info");
	spdlog::debug("info");

	if (!glfwInit()) {
		cout << "init glfw failed" << endl;
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	auto window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window) return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	if (glewInit()) {
		cout << "init glew failed" << endl;
		return 1;
	}

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();

	do {
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("esfhie", nullptr);
		ImGui::TextColored(ImColor(1.0f, 0.0f, 0.0f, 1.0f), "red");
		ImGui::SameLine();
		ImGui::TextColored(ImColor(0.0f, 1.0f, 0.0f, 1.0f), "green");
		ImGui::End();

		ssink->draw_imgui();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	} while (!glfwWindowShouldClose(window));

	return 0;
}
