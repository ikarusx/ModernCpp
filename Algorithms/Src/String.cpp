
#include "Precompiled.hpp"

#include "String.hpp"

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
int String::AToI(std::string str)
{
	int size = static_cast<int>(str.size());

	if (size == 0)
	{
		return 0;
	}

	int currIndex = str.find_first_not_of(' ');

	if (currIndex >= size)
	{
		return 0;
	}

	bool isPositive = str[currIndex] != '-';

	if (!(isPositive && str[currIndex] != '+'))
	{
		++currIndex;
	}
	int res = 0;
	int maxVal = (std::numeric_limits<int>::max)();
	int maxValBy10 = maxVal / 10;

	//isDigit
	while (currIndex < size && str[currIndex] >= '0' && str[currIndex] <= '9')
	{
		int tempRes = res * 10;
		int currVal = static_cast<int>(str[currIndex++] - '0');

		// Check if it will go oob (* and +).
		if (res > maxValBy10 || tempRes > maxVal - currVal)
		{
			return isPositive
				? (std::numeric_limits<int>::max)()
				: (std::numeric_limits<int>::min)();
		}

		res = tempRes + currVal;
	}

	return isPositive ? res : -res;
}
