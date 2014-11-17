#pragma once
#include <memory>

namespace auxT
{
	template<typename T>
	std::unique_ptr<T> make_unique()
	{
		return std::unique_ptr<T>(new T());
	}
}