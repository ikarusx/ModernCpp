
#ifndef _STACK_H_GUARD_
#define _STACK_H_GUARD_

#include <memory>
//#include <algorithm>

template<class T>
class Stack
{
public:
	Stack() noexcept;
	Stack(size_t capacity);

	// Rule of six:
	Stack(const Stack& other);
	Stack(Stack&& other) noexcept;

	Stack& operator=(const Stack& other);
	Stack& operator=(Stack&& other) noexcept;

	~Stack() noexcept;

	void Push(const T& val);
	T Top();
	void Pop();

	size_t Size() { return mCurrentIndex; }

private:
	void Grow();

	std::unique_ptr<T[]> mData{ nullptr }; // not allowing std::vector
	size_t mCapacity{ 0 };
	size_t mCurrentIndex{ 0 };
	bool mCanGrow{ true };
	
};

#pragma region ConstructDestruct
template<class T>
Stack<T>::Stack() noexcept
{
}

template<class T>
Stack<T>::Stack(size_t capacity)
	: mCapacity{ capacity }
{
	mData = std::make_unique<T[]>(capacity);
}

template<class T>
Stack<T>::Stack(const Stack& other)
	: mData{ std::make_unique<T[]>(other.mCapacity) }
	, mCapacity{ other.mCapacity }
	, mCurrentIndex{ other.mCurrentIndex }
	, mCanGrow{ other.mCanGrow }
{
	std::copy(other.mData.get(), other.mData.get() + mCapacity, mData.get());
}

template<class T>
Stack<T>::Stack(Stack&& other) noexcept
	: mData{ std::move(other.mData) }
	, mCapacity{ other.mCapacity }
	, mCurrentIndex{ other.mCurrentIndex }
	, mCanGrow{ other.mCanGrow }
{
	other.mData = nullptr;
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
	if (other == *this)
	{
		return;
	}

	mData.release();
	mData = std::make_unique<T[]>(other.mCapacity);
	mCapacity = other.mCapacity;
	mCurrentIndex = other.mCurrentIndex;
	mCanGrow = other.mCanGrow;

	std::copy(other.mData.get(), other.mData.get() + mCapacity, mData.get());
}

template<class T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept
{
	mData = std::move(other.mData);
	mCapacity = other.mCapacity;
	mCurrentIndex = other.mCurrentIndex;
	mCanGrow = other.mCanGrow;

	other.mData = nullptr;
}

template<class T>
Stack<T>::~Stack() noexcept
{
	mData.release();
}
#pragma endregion

template<class T>
void Stack<T>::Push(const T& val)
{
	if (mCurrentIndex >= mCapacity)
	{
		Grow();
	}

	mData[mCurrentIndex++] = val;
}

template<class T>
T Stack<T>::Top()
{
	static_assert(mCapacity > 0, "[Stack::Top] No elements in the stack!");

	return mData[mCurrentIndex - 1];
}

template<class T>
void Stack<T>::Pop()
{
	if (mCurrentIndex > 0)
	{
		--mCurrentIndex;
	}
}

template<class T>
void Stack<T>::Grow()
{
	if (mCapacity == 0)
	{
		mCapacity = 2;
		mData = std::make_unique<T[]>(mCapacity);
	}
	else
	{
		mCapacity = mCapacity << 1;
		std::unique_ptr<T[]> temp = std::make_unique<T[]>(mCapacity);

		std::copy(mData.get(), mData.get() + mCapacity, temp.get());
		mData.swap(temp);
	}
}

#endif //_STACK_H_GUARD_
