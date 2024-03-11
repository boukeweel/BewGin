#pragma once
#define WIN32_LEAN_AND_MEAN


#include "Singleton.h"
//#pragma comment(lib,"xinput.lib")

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();

	};

}
