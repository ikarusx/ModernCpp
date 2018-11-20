
#include "Precompiled.hpp"

#include "CString.hpp"

#include <limits>
#include <string>
#include <iostream>

using namespace Algorithms;

namespace
{
	static const auto speedup = []() {
		std::ios::sync_with_stdio(false);
		std::cin.tie(NULL);

		return 0;
	}();
}

// No std algorithms.
int CString::AToI(const char* str)
{
	if (str == nullptr)
	{
		return 0;
	}

	int currIndex = 0;

	while (str[currIndex] == ' ')
	{
		++currIndex;
	}

	if (str[currIndex] == '\0')
	{
		return 0;
	}

	bool isPositive = str[currIndex] != '-';

	if (!(isPositive && str[currIndex] != '+'))
	{
		++currIndex;
	}
	int res = 0;
	int maxVal = INT_MAX;
	int maxValBy10 = maxVal / 10;

	while (str[currIndex] >= '0' && str[currIndex] <= '9')
	{
		int tempRes = res * 10;
		int currVal = (int)(str[currIndex++] - '0');

		// Check if it will go oob (* and +).
		if (res > maxValBy10 || tempRes > maxVal - currVal)
		{
			return isPositive
				? INT_MAX
				: INT_MIN;
		}

		res = tempRes + currVal;
	}

	return isPositive ? res : -res;
}
