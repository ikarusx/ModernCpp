
#ifndef _SHAREDPTR_HPP_GUARD_
#define _SHAREDPTR_HPP_GUARD_

#include <functional>

template<typename T>
class SharedPtr
{
public:
	using ElementType = std::remove_extent_t<T>;
	using WeakType = std::weak_ptr<T>;

	constexpr SharedPtr() noexcept {}
	constexpr SharedPtr(std::nullptr_t) noexcept {}
	template<typename U, typename = typename std::enable_if<std::is_convertible<U*, T*>::value>::type>
	explicit SharedPtr(U* ptr);
	template<typename U, typename Deleter, typename = typename std::enable_if<std::is_convertible<U*, T*>::value>::type>
	SharedPtr(U* ptr, Deleter d);
	template<typename U, typename Deleter, typename = typename std::enable_if<std::is_convertible<U*, T*>::value>::type>
	SharedPtr(std::nullptr_t ptr, Deleter d);

	// Rule of six:
	SharedPtr(const SharedPtr& other);
	SharedPtr(SharedPtr&& other) noexcept;

	SharedPtr& operator=(const SharedPtr& other);
	SharedPtr& operator=(SharedPtr&& other) noexcept;

	~SharedPtr() noexcept;

	T* Get() { return mData; }
	T& operator*() {}

	void Swap(SharedPtr& sptr) noexcept;
	
	void reset() noexcept;
	template<typename U>
	void reset(U* ptr);
	template<typename U, typename Deleter>
	void reset(U* ptr, Deleter d);
	template<typename U, typename Deleter, typename Alloc>
	void reset(U* ptr, Deleter d, Alloc alloc);

private:
	T* mData{ nullptr };
	size_t mCount{ 0 };
	// TODO: test this later.
	std::function<void(T*)> mDeleter{ [](T* ptr) {
		if constexpr (!std::is_array<T>::value) delete ptr;
		else delete[] ptr;
	} };
};

#pragma region ConstructDestruct
template<typename T>
template<typename U, typename>
SharedPtr<T>::SharedPtr(U* ptr)
	: mData{ (T*)ptr }
{
}
template<typename T>
template<typename U, typename Deleter, typename>
SharedPtr<T>::SharedPtr(U* ptr, Deleter d)
	: mData{ (T*)ptr }
{
}
template<typename T>
template<typename U, typename Deleter, typename>
SharedPtr<T>::SharedPtr(std::nullptr_t ptr, Deleter d)
{
}

// Rule of six:
template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{

}
template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept
{

}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{

}
template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept
{

}

template<typename T>
SharedPtr<T>::~SharedPtr() noexcept
{
	if (mData != nullptr)
	{
		mDeleter(mData);
	}
}
#pragma endregion

#endif //_SHAREDPTR_HPP_GUARD_
