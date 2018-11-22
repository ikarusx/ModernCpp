
#ifndef _SINGLYLINKEDLIST_HPP_GUARD_
#define _SINGLYLINKEDLIST_HPP_GUARD_

#include <memory>

template<typename T>
class SinglyLinkedList
{
public:
	SinglyLinkedList() noexcept = default;

	// Rule of six:
	SinglyLinkedList(const SinglyLinkedList& other);
	SinglyLinkedList(SinglyLinkedList&& other) noexcept;

	SinglyLinkedList& operator=(const SinglyLinkedList& other);
	SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;

	~SinglyLinkedList() noexcept;

	struct Node
	{
		T data{};
		std::unique_ptr<Node> next{ nullptr };

		Node(T newData, std::unique_ptr<Node>&& newNext)
			: data{ newData }
			, next{ std::move(newNext) }
		{
		}

		Node(T&& newData, std::unique_ptr<Node>&& newNext)
			: data{ std::forward(newData) }
			, next{ std::move(newNext) }
		{
		}
	};

	size_t size() const;

	void push_back(const T& data);
	void push_back(T&& data);
	void push_front(const T& data);
	void push_front(T&& data);

	template<typename... Args>
	T& emplace_back(Args&&... args);
	template<typename... Args>
	T& emplace_front(Args&&... args);

private:
	std::unique_ptr<Node> head{ nullptr };
	Node* tail{ nullptr };
	size_t size{ 0 };

};

#pragma region ConstructDestruct
// Rule of six:
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other)
	: head{ std::make_unique<Node>(other.head) }
{
	for (int i = 0; i < other.size(); ++i)
	{
		//push_back(other.);
	}
}
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& other) noexcept
	: tail{ other.tail }
	, head{ std::move(other.head) }
{
}
template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& other)
{
}
template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList&& other) noexcept
{
}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() noexcept
{
}
#pragma endregion //ConstructDestruct

template<typename T>
size_t SinglyLinkedList<T>::size() const
{
	return size;
}

template<typename T>
void SinglyLinkedList<T>::push_back(const T& data)
{
	if (tail != nullptr)
	{
		tail->next = std::make_unique<Node>(data, nullptr);
		tail = tail->next.get();
	}
	else
	{
		head = std::make_unique<Node>(data, nullptr);
		tail = head.get();
	}
}
template<typename T>
void SinglyLinkedList<T>::push_back(T&& data)
{
	if (tail != nullptr)
	{
		tail->next = std::make_unique<Node>(std::move(data), nullptr);
		tail = tail->next.get();
	}
	else
	{
		head = std::make_unique<Node>(std::move(data), nullptr);
		tail = head.get();
	}
}
template<typename T>
void SinglyLinkedList<T>::push_front(const T& data)
{
}
template<typename T>
void SinglyLinkedList<T>::push_front(T&& data)
{
}

template<typename T>
template<typename... Args>
T& SinglyLinkedList<T>::emplace_back(Args&&... args)
{
	return T{};
}
template<typename T>
template<typename... Args>
T& SinglyLinkedList<T>::emplace_front(Args&&... args)
{
	return T{};
}

#endif //_SINGLYLINKEDLIST_HPP_GUARD_
