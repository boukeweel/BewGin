#include "GameTime.h"

void dae::GameTime::Update()
{
	s_CurrentTime = std::chrono::high_resolution_clock::now();
	s_DeltaTime = std::chrono::duration<double>(s_CurrentTime - s_LastTime).count();
	s_LastTime = s_CurrentTime;
}
