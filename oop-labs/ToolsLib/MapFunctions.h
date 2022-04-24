#pragma once
#include "pch.h"

class MapFunctions
{
public:
	template<typename _It, typename _Pred>
	static std::vector<_It> FindAll(_It start, _It end, _Pred predicate);
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
