#include "imguiManager.h"

#include <chrono>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

void imguiManager::Init(SDL_Window* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void imguiManager::Render() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	//make imgui code here
	GraphsExOne();

	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void imguiManager::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void imguiManager::GraphsExOne() const
{
	ImGui::Begin("Graph");
	int samples = 2;
	

	if (ImGui::Button("Trash the cache")) {
		// Button was clicked, call your function
		m_DurationsExOne.clear();
		m_DurationsExOne = MeasureExOne(samples);
	}

	if(!m_DurationsExOne.empty())
		ImGui::PlotLines("", m_DurationsExOne.data(), static_cast<int>(m_DurationsExOne.size()), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(200, 80));

	ImGui::End();
}

std::vector<float> imguiManager::MeasureExOne(int samples) const
{
	const int size = 100000000;
	int* buffer = new int[size];

	std::vector<float> durations;

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		long long duration = 0;

		for (int Sampel = 0; Sampel < samples; ++Sampel)
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < size; i += stepsize)
			{
				buffer[i] *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		}

		duration /= samples;
		durations.push_back(static_cast<float>(duration));

	}
	CleanUpMeasurements(durations);

	return durations;
}

//std::vector<float> imguiManager::MeasureExTwo(int /*samples*/) const
//{
//	
//}


void imguiManager::CleanUpMeasurements(std::vector<float>& durations) const
{
	auto minIndex = std::min_element(durations.begin(), durations.end()) - durations.begin();
	auto maxIndex = std::max_element(durations.begin(), durations.end()) - durations.begin();

	durations.erase(durations.begin() + std::max(minIndex, maxIndex));
	durations.erase(durations.begin() + std::min(minIndex, maxIndex));
}

