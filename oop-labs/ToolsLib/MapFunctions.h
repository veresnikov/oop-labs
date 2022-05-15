#pragma once
#include "pch.h"

class MapFunctions
{
public:
	template <typename _It, typename _Pred>
	static std::vector<_It> FindAll(_It start, _It end, _Pred predicate);
	template <typename K, typename V, typename _Pred>
	static std::vector<std::pair<K, V>> Sort(std::map<K, V> const& map, _Pred predicate);
};

template <typename _It, typename _Pred>
std::vector<_It> MapFunctions::FindAll(_It start, _It end, _Pred predicate)
{
	std::vector<_It> result;
	_It curr = start;
	do
	{
		auto v = std::find_if(curr, end, predicate);
		if (v == end)
		{
			break;
		}
		result.push_back(v);
		++v;
		curr = v;
	} while (true);
	return result;
}

template <typename K, typename V, typename _Pred>
inline std::vector<std::pair<K, V>> MapFunctions::Sort(std::map<K, V> const& map, _Pred predicate)
{
	std::vector<std::pair<K, V>> result;
	std::transform(map.begin(), map.end(), std::back_inserter(result), [](std::pair<K, V> item) { return item; });
	std::sort(result.begin(), result.end(), predicate);
	return result;
}
