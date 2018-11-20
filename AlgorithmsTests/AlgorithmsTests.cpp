#include "stdafx.h"
#include "CppUnitTest.h"

#include <Algorithms/Inc/Algorithms.hpp>

#include <string>
#include <vector>
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Algorithms;

namespace AlgorithmsTests
{		
	TEST_CLASS(CStringTests)
	{
	public:
		
		TEST_METHOD(atoiPerfectCases)
		{
			char str1[] = "132";
			char str2[] = "+345";
			char str3[] = "-987";

			Assert::AreEqual(CString::AToI(str1), 132);
			Assert::AreEqual(CString::AToI(str2), 345);
			Assert::AreEqual(CString::AToI(str3), -987);
		}

		TEST_METHOD(atoiEdgeCases)
		{
			std::vector<std::string> strs{
				"132a232", "+abc", "-def", "   +123", "    abc",
				"      ", "12345678910", "-12345678910",
				"+0932", "-0932", " 0932", "2147483646", "-6147483648"
			};

			Assert::AreEqual(CString::AToI(strs[0].c_str()), 132);
			Assert::AreEqual(CString::AToI(strs[1].c_str()), 0);
			Assert::AreEqual(CString::AToI(strs[2].c_str()), 0);
			Assert::AreEqual(CString::AToI(strs[3].c_str()), 123);
			Assert::AreEqual(CString::AToI(strs[4].c_str()), 0);
			Assert::AreEqual(CString::AToI(strs[5].c_str()), 0);
			Assert::AreEqual(CString::AToI(strs[6].c_str()), (std::numeric_limits<int>::max)());
			Assert::AreEqual(CString::AToI(strs[7].c_str()), (std::numeric_limits<int>::min)());
			Assert::AreEqual(CString::AToI(strs[8].c_str()), 932);
			Assert::AreEqual(CString::AToI(strs[9].c_str()), -932);
			Assert::AreEqual(CString::AToI(strs[10].c_str()), 932);
			Assert::AreEqual(CString::AToI(strs[11].c_str()), 2147483646);
			Assert::AreEqual(CString::AToI(strs[12].c_str()), (std::numeric_limits<int>::min)());
		}

	};
}