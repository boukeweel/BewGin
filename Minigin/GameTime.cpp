#include "GameTime.h"

void bew::GameTime::Update()
{
	s_CurrentTime = std::chrono::high_resolution_clock::now();
	s_DeltaTime = std::min(s_MaxDeltatTime,std::chrono::duration<double>(s_CurrentTime - s_LastTime).count());
	s_LastTime = s_CurrentTime;
}
