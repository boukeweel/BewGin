#pragma once
#include <cstdlib>

namespace bew
{
	class RandomFunctions final
	{
	public:
		[[nodiscard]] static float RandomF() {return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);}
		[[nodiscard]] static float RandomF(float max){ return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)); }
		[[nodiscard]] static float RandomF(float min, float max){return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));}

		[[nodiscard]] static int RandomI(){ return rand(); }
		[[nodiscard]] static int RandomI(int max){ return rand() % max; }
		[[nodiscard]] static int RandomI(int min, int max){ return min + rand() % (max - min + 1); }
	};
}



