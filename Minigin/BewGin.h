#pragma once
#include <string>
#include <functional>

namespace bew
{
	const static int ScreenWidth{ 640 };
	const static int ScreenHeight{ 520 };

	class BewGin final 
	{
	public:
		explicit BewGin(const std::string& dataPath);
		~BewGin();
		void Run(const std::function<void()>& load);

		BewGin(const BewGin& other) = delete;
		BewGin(BewGin&& other) = delete;
		BewGin& operator=(const BewGin& other) = delete;
		BewGin& operator=(BewGin&& other) = delete;

	private:
		double m_Lag{0};
	};
}