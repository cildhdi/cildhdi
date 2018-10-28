#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include <memory>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cstddef>

namespace ll
{
	template<typename T>
	class LinkList;
	template<typename T>
	class LinkListIterator;

	template<typename T>
	class Node
	{
	private:
		T _data;
		Node* _next;
		friend class LinkList<T>;
		friend class LinkListIterator<T>;

		explicit Node(const T& data = T()) : _data(data), _next(nullptr)
		{
		}

		template<typename... Args>
		Node(Args&&... args)
		{
			_data = T(args...);
			_next = nullptr;
		}

		explicit Node(T&& data)
		{
			_data = std::move(data);
			_next = nullptr;
		}
		Node(const Node& other)
		{
			_data = other._data;
			_next = other._next;
		}
	};

	//Iterator
	template<typename T>
	class LinkListIterator :public std::iterator<std::forward_iterator_tag, T>
	{
		friend class Node<T>;
		friend class LinkList<T>;
	private:
		LinkList<T>* _list;
		Node<T>* _node;
	public:
		LinkListIterator(LinkList<T>* list = nullptr, Node<T>* node = nullptr) : _list(list), _node(node)
		{
		}

		LinkListIterator(const LinkListIterator& other) : _list(other._list), _node(other._node)
		{
		}

		bool valid() const
		{
			return _list != nullptr && _node != nullptr;
		}

		T& operator*()
		{
			if (valid())
				return _node->_data;
			else
				throw std::out_of_range("invalid iterator");
		}

		LinkListIterator operator++(int)
		{
			if (valid())
			{
				LinkListIterator it = *this;
				_node = _node->_next;
				return it;
			}
			else
			{
				throw std::out_of_range("invalid iterator");
			}
		}

		LinkListIterator operator+(unsigned int d)
		{
			LinkListIterator it = *this;
			while (d--)
				it++;
			return it;
		}

		LinkListIterator operator+=(unsigned int d)
		{
			*this = (*this + d);
			return *this;
		}

		bool operator==(const LinkListIterator& rhs)
		{
			return _node == rhs._node;
		}

		bool operator!=(const LinkListIterator& rhs)
		{
			return _node != rhs._node;
		}
	};


	//LinkList
	template<typename T>
	class LinkList
	{
	public:
		using ValueType = T;
		using SizeType = std::size_t;
		using DifferenceType = std::ptrdiff_t;
		using Reference = ValueType & ;
		using Pointer = ValueType * ;
		using ConstPointer = const ValueType*;
		using NodeType = Node<T>;
		using Iterator = LinkListIterator<T>;
	private:
		Node<T>* _head = nullptr;
		size_t _size = 0;
	public:
		LinkList()
		{
			_head = nullptr;
			_size = 0;
		}

		LinkList(SizeType count, const ValueType& value = ValueType())
		{
			if (!count) return;
			_size = count;
			NodeType* previous = new NodeType(value);
			_head = previous;
			while (--count)
			{
				previous->_next = new Node<T>(value);
				previous = previous->_next;
			}
		}

		LinkList(const LinkList& other)
		{
			*this = other;
		}

		LinkList(LinkList&& other)
		{
			*this = std::move(other);
		}

		LinkList(std::initializer_list<T> init_list)
		{
			*this = init_list;
		}

		virtual ~LinkList()
		{
			clear();
		}

		LinkList& operator=(const LinkList& other)
		{
			if (other.empty()) return *this;
			_size = other._size;
			NodeType* other_previous = other._head;
			NodeType* previous = new NodeType(other_previous->_data);
			_head = previous;
			SizeType count = _size;
			while (--count)
			{
				previous->_next = new Node<T>(other_previous->_next->_data);
				previous = previous->_next;
				other_previous = other_previous->_next;
			}
			return *this;
		}

		LinkList& operator=(LinkList&& other)
		{
			_head = other._head;
			_size = other._size;
			other._head = nullptr;
			other._size = 0;
			return *this;
		}

		LinkList& operator=(std::initializer_list<T> init_list)
		{
			if (init_list.size() == 0) return *this;
			for (size_t index = init_list.size(); index != 0; index--)
			{
				push_front(*(init_list.begin() + index - 1));
			}
			return *this;
		}

		bool empty() const noexcept
		{
			return _size == 0;
		}
	public: //ÐÞ¸Ä
		void clear() noexcept
		{
			if (_size == 0) return;
			NodeType* ptr = _head, *temp;
			while (!ptr)
			{
				temp = ptr;
				ptr = ptr->_next;
				delete temp;
			}
			_head = nullptr;
			_size = 0;
		}

		void push_front(const T& value)
		{
			NodeType* new_head = new NodeType(value);
			new_head->_next = _head;
			_head = new_head;
			_size++;
		}

		void push_front(T&& value)
		{
			NodeType* new_head = new NodeType(std::move(value));
			new_head->_next = _head;
			_head = new_head;
			_size++;
		}

		template<typename... Args>
		void emplace_front(Args&&... args)
		{
			NodeType* new_head = new NodeType(std::forward<Args>(args)...);
			new_head->_next = _head;
			_head = new_head;
			_size++;
		}

		void pop_front()
		{
			if (empty()) return;
			NodeType* old = _head;
			_head = _head->_next;
			delete old;
			_size--;
		}

		Iterator begin()
		{
			return Iterator(this, _head);
		}

		Iterator end()
		{
			return Iterator(this, nullptr);
		}

		Iterator insert_after(Iterator pos, const ValueType& value)
		{
			NodeType* node = new NodeType(value);
			node->_next = pos._node->_next;
			pos._node->_next = node;
			_size++;
			return Iterator(this, node);
		}

		Iterator insert_after(Iterator pos, ValueType&& value)
		{
			NodeType* node = new NodeType(std::move(value));
			node->_next = pos._node->_next;
			pos._node->_next = node;
			_size++;
			return Iterator(this, node);
		}

		Iterator insert_after(Iterator pos, SizeType count, const T& value)
		{
			if (count == 0) return pos;
			while (count--)
			{
				pos = insert_after(pos, value);
			}
			return pos;
		}

		Iterator insert_after(Iterator pos, Iterator first, Iterator last)
		{
			Iterator it = first;
			while (it != last)
			{
				pos = insert_after(pos, *it);
				it++;
			}
			return pos;
		}

		Iterator erase_after(Iterator pos)
		{
			if (!pos.valid()) return pos;
			NodeType* old = pos._node->_next;
			if (old) pos._node->_next = old->_next;
			delete old;
			_size--;
			return Iterator(this, pos._node->_next);
		}

		Iterator erase_after(Iterator first, Iterator last)
		{
			NodeType* temp = first._node->_next, *old;
			first._node->_next = last._node;
			SizeType count = 0;
			while (temp != last._node)
			{
				old = temp;
				temp = temp->_next;
				delete old;
				count++;
			}
			_size -= count;
			return last;
		}

		void resize(SizeType count, const ValueType& value = ValueType())
		{
			if (count > _size)
			{
				NodeType* node = _head;
				while (node->_next != nullptr)
					node = node->_next;
				insert_after(Iterator(this, node), count - _size, value);
			}
			else if (count < _size)
			{
				NodeType* node = _head;
				while (--count)
					node = node->_next;
				erase_after(Iterator(this, node), end());
			}
		}

		void swap(LinkList& other)
		{
			std::swap(_head, other._head);
			std::swap(_size, other._size);
		}

		void splice_after(Iterator pos, LinkList&& other)
		{
			SizeType count = other._size;
			NodeType* head = other._head, *temp = head;
			other._head = nullptr;
			other._size = 0;
			while (temp->_next != nullptr)
				temp = temp->_next;
			temp->_next = pos._node->_next;
			pos._node->_next = head;
			_size += count;
		}

		void splice_after(Iterator pos, LinkList& other)
		{
			splice_after(pos, std::move(other));
		}

		void splice_after(Iterator pos, LinkList&& other, Iterator first, Iterator last)
		{
			if (first == last || first + 1 == last) return;
			NodeType* node = first._node->_next;
			SizeType count = 1;
			while (node->_next != last._node)
			{
				node = node->_next;
				count++;
			}
			node->_next = pos._node->_next;
			pos._node->_next = first._node->_next;
			first._node->_next = last._node;
			_size += count;
			other._size -= count;
		}

		void splice_after(Iterator pos, LinkList& other, Iterator first, Iterator last)
		{
			splice_after(pos, std::move(other), first, last);
		}

		void splice_after(Iterator pos, LinkList& other, Iterator it)
		{
			splice_after(pos, std::move(other), it, it + 2);
		}

		Iterator remove(Iterator it)
		{
			if (!it.valid()) return it;
			NodeType* old = it._node, *node = _head;
			while (node->_next != old)
				node = node->_next;
			node->_next = old->_next;
			delete old;
			_size--;
			return Iterator(this, node->_next);
		}

		SizeType remove(const ValueType& value)
		{
			return remove_if([&](const ValueType& v)
			{
				return v == value;
			});
		}

		template<typename Predicate>
		SizeType remove_if(Predicate p)
		{
			Iterator it = begin();
			SizeType count = 0;
			while (it != end())
			{
				if (p(*it))
				{
					it = remove(it);
					count++;
				}
				else
				{
					it++;
				}
			}
			return count;
		}

		void reverse() noexcept
		{
			if (empty()) return;
			NodeType** buffer = new NodeType*[_size], *node = _head;
			for (SizeType i = 0; node != nullptr; node = node->_next, i++)
				buffer[i] = node;
			std::reverse(buffer, buffer + _size);
			for (SizeType i = 0; i < _size - 1; i++)
				buffer[i]->_next = buffer[i + 1];
			buffer[_size - 1]->_next = nullptr;
			_head = buffer[0];
			delete buffer;
		}

		template<typename Compare>
		void sort(Compare cmp) noexcept
		{
			if (empty()) return;
			NodeType** buffer = new NodeType*[_size], *node = _head;
			for (SizeType i = 0; node != nullptr; node = node->_next, i++)
				buffer[i] = node;
			std::sort(buffer, buffer + _size, [&](const NodeType* lhs, const NodeType* rhs)
			{
				return cmp(lhs->_data, rhs->_data);
			});
			for (SizeType i = 0; i < _size - 1; i++)
				buffer[i]->_next = buffer[i + 1];
			buffer[_size - 1]->_next = nullptr;
			_head = buffer[0];
			delete buffer;
		}
	};
}

#endif