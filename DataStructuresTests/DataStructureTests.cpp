#include "stdafx.h"
#include "CppUnitTest.h"

#include <DataStructures/Inc/Stack.h>

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
}