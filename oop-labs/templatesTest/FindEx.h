#pragma once
#include <vector>

namespace task1
{
template <typename T, typename Predicate>
inline bool FindMax(const std::vector<T>& arr, T& maxValue, const Predicate& predicate)
{
	if (arr.empty())
	{
		return false;
	}
	size_t findPosition = 0;
	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (predicate(arr[findPosition], arr[i]))
		{
			findPosition = i;
		}
	}
	maxValue = arr[findPosition];
	return true;
}}
