#include "ImGuiTrashTheCacheComponent.h"

#include <chrono>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

dae::ImGuiTrashTheCacheComponent::ImGuiTrashTheCacheComponent(GameObject* pParentObject): Component(pParentObject)
{
}

void dae::ImGuiTrashTheCacheComponent::Render() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	//make imgui code here
	GraphsExOne();
	GraphsExTwo();
	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void dae::ImGuiTrashTheCacheComponent::GraphsExOne() const
{
	ImGui::Begin("Graph ex1");

	int samples = 20;
	ImGui::InputInt("sample", &samples);

	if (ImGui::Button("Trash the cache")) {
		m_DurationsExOne.clear();
		m_DurationsExOne = MeasureExOne(samples);
	}

	if(!m_DurationsExOne.empty())
		ImGui::PlotLines("", m_DurationsExOne.data(), static_cast<int>(m_DurationsExOne.size()), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(200, 80));

	ImGui::End();
}

void dae::ImGuiTrashTheCacheComponent::GraphsExTwo() const
{
	ImGui::Begin("Graph ex2");

	int samples = 20;
	ImGui::InputInt("sample", &samples);

	if (ImGui::Button("Trash the cache with gameobject3d")) {
		m_DurationsExTwo.clear();
		m_DurationsExTwo = MeasureExTwo(samples);
	}

	if (ImGui::Button("Trash the cache with gameobject3dAlt")) {
		m_DurationsExTwoAlt.clear();
		m_DurationsExTwoAlt = MeasureExTwoAlt(samples);
	}

	if (!m_DurationsExTwo.empty())
		ImGui::PlotLines("", m_DurationsExTwo.data(), static_cast<int>(m_DurationsExTwo.size()), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(200, 80));
	if (!m_DurationsExTwoAlt.empty())
		ImGui::PlotLines("", m_DurationsExTwoAlt.data(), static_cast<int>(m_DurationsExTwoAlt.size()), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(200, 80));


	//dont know how to compine 2 graphs
	//if(!m_DurationsExTwo.empty() && !m_DurationsExTwoAlt.empty())
	//{
	//	ImGui::PlotLines("", m_DurationsExTwo.data(), static_cast<int>(m_DurationsExTwo.size()), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(200, 80));
	//	ImGui::PlotLines("", m_DurationsExTwoAlt.data(), static_cast<int>(m_DurationsExTwoAlt.size()), 0, NULL, FLT_MAX, FLT_MAX, ImVec2(200, 80));
	//}
	ImGui::End();
}


std::vector<float> dae::ImGuiTrashTheCacheComponent::MeasureExOne(int samples) const
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
	delete buffer;
	return durations;
}

std::vector<float> dae::ImGuiTrashTheCacheComponent::MeasureExTwo(int samples) const
{
	const int size = 10000000;
	GameObject3D* buffer = new GameObject3D[size];

	std::vector<float> durations;

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		long long duration = 0;

		for (int Sampel = 0; Sampel < samples; ++Sampel)
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < size; i += stepsize)
			{
				buffer[i].ID *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			 duration += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		}
		duration /= samples;

		durations.push_back(static_cast<float>(duration));

	}

	CleanUpMeasurements(durations);
	delete buffer;
	return durations;
}

std::vector<float> dae::ImGuiTrashTheCacheComponent::MeasureExTwoAlt(int samples) const
{
	const int size = 10000000;
	GameObject3DAlt* buffer = new GameObject3DAlt[size];

	std::vector<float> durations;

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		long long duration = 0;

		for (int Sampel = 0; Sampel < samples; ++Sampel)
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < size; i += stepsize)
			{
				buffer[i].ID *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			duration += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		}
		duration /= samples;

		durations.push_back(static_cast<float>(duration));

	}

	CleanUpMeasurements(durations);
	delete buffer;
	return durations;
}


void dae::ImGuiTrashTheCacheComponent::CleanUpMeasurements(std::vector<float>& durations) const
{
	auto minIndex = std::min_element(durations.begin(), durations.end()) - durations.begin();
	auto maxIndex = std::max_element(durations.begin(), durations.end()) - durations.begin();

	durations.erase(durations.begin() + std::max(minIndex, maxIndex));
	durations.erase(durations.begin() + std::min(minIndex, maxIndex));
}

