#include "stdafx.h"
#include "CppUnitTest.h"

#include <DataStructures/Inc/DataStructures.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructuresTests
{		
	TEST_CLASS(StackTests)
	{
	public:
		
		TEST_METHOD(PushElementAndTop)
		{
			Stack<int> myStack;

			myStack.Push(10);

			Assert::IsTrue(myStack.Top() == 10);
		}

		TEST_METHOD(PushPushTopPopTop)
		{
			Stack<int> myStack;

			myStack.Push(10);
			myStack.Push(5);

			Assert::IsTrue(myStack.Top() == 5);
			myStack.Pop();
			Assert::IsTrue(myStack.Top() == 10);
		}

		TEST_METHOD(PushPopSize)
		{
			Stack<int> myStack(2);

			Assert::IsTrue(myStack.Size() == 0);
			myStack.Push(10);
			Assert::IsTrue(myStack.Size() == 1);
			myStack.Push(5);
			Assert::IsTrue(myStack.Size() == 2);
			myStack.Pop();
			Assert::IsTrue(myStack.Size() == 1);
			myStack.Pop();
			Assert::IsTrue(myStack.Size() == 0);
		}

	};

	TEST_CLASS(SharedPtrTests)
	{
	public:

		TEST_METHOD(ConstructAndDestroy)
		{
			SharedPtr<int> mySharedPtr;

			Assert::IsNull(mySharedPtr.Get());
		}

		TEST_METHOD(PointerContruction)
		{
			int* ip{ new int{ 5 } };
			SharedPtr<int> mySharedPtr(ip);

			Assert::IsNotNull(mySharedPtr.Get());
			Assert::AreEqual(mySharedPtr.Get(), ip);
			Assert::AreEqual(*mySharedPtr.Get(), 5);

			//float* fp{ new float{ 5.5f } };
			//SharedPtr<int> mySharedPtrFloatToInt{ fp };
			//Assert::Fail(std::to_wstring(std::is_convertible<float, int>::value).c_str());
		}

		TEST_METHOD(ScopeDestruction)
		{
			int* ip{ new int{ 5 } };
			{
				SharedPtr<int> mySharedPtr(ip);

				Assert::IsNotNull(mySharedPtr.Get());
				Assert::IsNotNull(ip);
			}
			Assert::AreNotEqual(*ip, 5);
		}

		TEST_METHOD(DeleterConstruction)
		{
			int* ip{ new int{ 5 } };
			{
				SharedPtr<int> mySharedPtr{ ip, [](int* ptr) { delete ptr; } };

				Assert::IsNotNull(mySharedPtr.Get());
				Assert::IsNotNull(ip);
			}
			Assert::AreNotEqual(*ip, 5);

			std::shared_ptr<int> test1;
			std::shared_ptr<int> test2{ test1 };
			std::shared_ptr<int> test3{ std::make_shared<int>(10) };

			test2.swap(test3);

			Assert::IsFalse((bool)test1);
			Assert::IsTrue((bool)test2);
			Assert::IsFalse((bool)test3);
			Assert::AreEqual(test1.use_count(), test3.use_count());
		}

	};
}