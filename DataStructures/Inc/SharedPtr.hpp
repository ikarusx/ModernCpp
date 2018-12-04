
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
	inline explicit SharedPtr(U* ptr) noexcept;
	template<typename U, typename Deleter, typename = typename std::enable_if<std::is_convertible<U*, T*>::value>::type>
	inline SharedPtr(U* ptr, Deleter d) noexcept;
	template<typename U, typename Deleter, typename = typename std::enable_if<std::is_convertible<U*, T*>::value>::type>
	inline SharedPtr(std::nullptr_t ptr, Deleter d) noexcept;

	// Rule of six:
	inline SharedPtr(const SharedPtr& other) noexcept;
	inline SharedPtr(SharedPtr&& other) noexcept;

	inline SharedPtr& operator=(const SharedPtr& other) noexcept;
	inline SharedPtr& operator=(SharedPtr&& other) noexcept;

	inline ~SharedPtr() noexcept;

	inline T* Get() noexcept { return mData; }
	inline T* Get() const noexcept { return mData; }
	inline T& operator*() const noexcept { return (*Get()); }
	inline T* operator->() const noexcept { return Get(); }

	inline void Swap(SharedPtr& sptr) noexcept;
	
	inline void reset() noexcept;
	template<typename U>
	inline void reset(U* ptr) noexcept;
	template<typename U, typename Deleter>
	inline void reset(U* ptr, Deleter d) noexcept;
	template<typename U, typename Deleter, typename Alloc>
	inline void reset(U* ptr, Deleter d, Alloc alloc) noexcept;

private:
	inline void IncrementRef() { ++mUseCount; }

	using DeleterType = void(T*);

	T* mData{ nullptr };
	size_t mUseCount{ 0 };
	size_t mWeakCount{ 0 };
	// TODO: test this later.
	std::function<DeleterType> mDeleter{ [](T* ptr) {
		if constexpr (!std::is_array<T>::value) delete ptr;
		else delete[] ptr;
	} };
};

#pragma region ConstructDestruct
template<typename T>
template<typename U, typename>
inline SharedPtr<T>::SharedPtr(U* ptr) noexcept
	: mData{ (T*)ptr }
{
}
template<typename T>
template<typename U, typename Deleter, typename>
inline SharedPtr<T>::SharedPtr(U* ptr, Deleter d) noexcept
	: mData{ static_cast<T*>(ptr) }
	, mDeleter{ std::move(d) }
{
}
template<typename T>
template<typename U, typename Deleter, typename>
inline SharedPtr<T>::SharedPtr(std::nullptr_t ptr, Deleter d) noexcept
	: mDeleter{ std::move(d) }
{
}

// Rule of six:
template<typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) noexcept
	: mData{ other.Get() }
	, mUseCount{ other.mUseCount + 1 }
	, mWeakCount{ other.mWeakCount }
{
	const_cast<SharedPtr<T>&>(other).IncrementRef();
}
template<typename T>
inline SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept
	: mData{ std::forward<T*>(other.mData) }
	, mUseCount{ other.mUseCount }
	, mWeakCount{ other.mWeakCount }
{
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) noexcept
{
	if (&other != this)
	{

	}
}
template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept
{
	if (&other != this)
	{
		
	}
}

template<typename T>
inline SharedPtr<T>::~SharedPtr() noexcept
{
	if (mData != nullptr)
	{
		mDeleter(mData);
	}
}
#pragma endregion

#endif //_SHAREDPTR_HPP_GUARD_
